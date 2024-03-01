#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

const int MAX_SIZE = 100; // số lượng phần tử tối đa của mảng
const char* DATA_PATH = "books.dat"; // đường dẫn tới file dữ liệu dùng đọc/ ghi

// Định nghĩa kiểu sách
struct Book {
    char maBook[50];
    char tenBook[50];
    char tacGia[50];
    char nhaXB[50];
    int namXB;
    float donGia;
    int soLuong;
    float thanhTien;
    float thueVAT;
    float thucTien;
};
typedef struct Book Book;

// Hàm nhập 1 cuốn sách
Book NhapBook(){
    Book book;
    cin.ignore();
    cout << "Nhap ma book: "; cin.getline(book.maBook, 50);
    cout << "Nhap ten book: "; cin.getline(book.tenBook, 50);
    cout << "Nhap ten TG: "; cin.getline(book.tacGia, 50);
    cout << "Nhap nha XB: "; cin.getline(book.nhaXB, 50);
    cout << "Nhap nam XB: "; cin >> book.namXB;
    cout << "Nhap don gia: "; cin >> book.donGia;
    cout << "Nhap so luong: "; cin >> book.soLuong;
    cout << "Nhap thue VAT: "; cin >> book.thueVAT;
    book.thanhTien = 0; // chưa tính thì khởi tạo là 0
    book.thucTien = 0;
    return book;
}

// Hàm nhập n cuốn sách
void NhapBooks(Book b[], int n){
    for (int i = 0; i < n; i++){
        cout << "Nhap book thu " << i + 1 << ":\n";
        Book book = NhapBook();
        b[i] = book;
        cout << "----------------------------\n";
    }
}

// Hàm in tiêu đề, phục vụ in danh sách dạng bảng
void InTieuDe(){
    cout << setw(20) << "Ma Book";
    cout << setw(20) << "Ten Book";
    cout << setw(20) << "Tac gia";
    cout << setw(20) << "Nha XB";
    cout << setw(20) << "Nam XB";
    cout << setw(20) << "Don gia";
    cout << setw(20) << "So luong";
    cout << setw(20) << "Thanh tien";
    cout << setw(20) << "Thue VAT";
    cout << setw(20) <<"Thuc tien" << "\n";
}

// hàm xuất thông tin 1 cuốn sách
void XuatBook(Book b){
    cout.setf(ios::fixed);
    cout << setw(20) << b.maBook;
    cout << setw(20) << b.tenBook;
    cout << setw(20) << b.tacGia;
    cout << setw(20) << b.nhaXB;
    cout << setw(20) << b.namXB;
    cout << setw(20) << b.donGia;
    cout << setw(20) << b.soLuong;
    cout << setprecision(2) << setw(20) << b.thanhTien;
    cout << setprecision(2) << setw(20) << b.thueVAT;
    cout << setprecision(2) << setw(20) << b.thucTien << "\n";
}

// Hàm xuất thông tin n cuốn sách
void XuatBooks(Book b[], int n){
    // gọi hàm in tiêu đề trước
    InTieuDe();
    // lặp để in ra thông tin từng cuốn
    for(int  i = 0; i < n; i++){
        XuatBook(b[i]);
    }
}

// hàm tính thành tiền cho n cuốn sách
void TinhThanhTien(Book b[], int n){
    for(int i = 0; i < n; i++){
        b[i].thanhTien = b[i].donGia * b[i].soLuong;
    }
}

// hàm tính thực tiền cho n cuốn sách
void TinhThucTien(Book b[], int n){
    for(int i = 0; i < n; i++){
        b[i].thucTien = b[i].thanhTien * (1 + b[i].thueVAT); // 100% số tiền + VAT * số tiền
    }
}

// Hàm sắp xếp giảm dần theo năm XB
void SapXep(Book b[], int n){
    for (int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            // Nếu cuốn trước có năm xuất bản nhỏ hơn cuốn sau thì hoán vị.
            // vì j = i + 1 nên j luôn ở sau i
            if (b[i].namXB < b[j].namXB){
                Book temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
}

// Hàm tìm và in thông tin sách có thực tiền lớn nhất.
void MaxSach(Book b[], int n){
    // khởi tạo cuốn đầu tiên là cuốn lớn nhất
    int maxTT = b[0].thucTien;
    int maxIndex = 0; // lưu chỉ số sách lớn nhất hiện tại
    for (int i = 1; i < n; i++){
        if (b[i].thucTien > maxTT){
            maxTT = b[i].thucTien;
            maxIndex = i;
        }
    }
    // in thông tin sách lớn nhất
    cout << "Sach co thuc tien lon nhat la:\n";
    InTieuDe(); // in tiêu đề
    XuatBook(b[maxIndex]); // in thông tin sách
}


// Hàm đếm số lượng cuốn sách, tính tổng số lượng
void TongSoCuonSach(Book b[], int n){
    int tong = 0;
    for(int i = 0; i < n; i++){
        tong += b[i].soLuong;
    }
    cout << "Tong so cuon sach la: " << tong << "\n";
}


// Hàm lọc theo thuế VAT, lặp và tìm cách sách có VAT lớn hơn thì in ra
void LocTheoVAT(Book b[], int n){
    float value;
    cout << "Nhap gia VAT toi thieu: ";
    cin >> value;
    int count = 0;
    for (int i = 0; i < n; i++){
        if (b[i].thueVAT > value){
            if (count == 0){
                // Nếu lần đầu tìm thấy thì in tiêu đề
                InTieuDe();
            }
            XuatBook(b[i]);
            count++;
        }
    }
    // Nếu tìm ko được cuốn nào thì báo ko có
    if (count == 0){
        cout << "Khong tim thay ket qua!\n";
    }
}

// Hàm ghi các cuốn sách ra file
void toFile(Book b[], int n){
    FILE *fptr; // con trỏ file
    fptr = fopen(DATA_PATH,"w"); // mở file
    if(fptr == NULL) {
      printf("Loi mo file!");   
      exit(EXIT_FAILURE);             // thoát chương trình nếu có lỗi mở file
   }
    fprintf(fptr,"%d\n", n); // dòng đầu tiên ghi số cuốn sách
    for (int i = 0; i < n; i++){
        // một cuốn sách ăn sẽ ghi 8 dòng, không ghi thành tiền & thực tiền vào file
        fprintf(fptr, "%s\n%s\n%s\n%s\n%d\n%f\n%d\n%f\n", b[i].maBook, b[i].tenBook, b[i].tacGia, b[i].nhaXB, b[i].namXB, b[i].donGia, b[i].soLuong, b[i].thueVAT);
    }
    printf("Ghi %d cuon sach thanh cong tai %s!\n", n, DATA_PATH);
    fclose(fptr); // đóng file
}

// Hàm đọc các cuốn sách từ file
// n là tham chiếu, vì ta cần thay đổi giá trị của n ở hàm main tại hàm này.
void fromFile(Book b[], int &n){
    FILE *fptr;
    fptr = fopen(DATA_PATH,"r");
    if(fptr == NULL) {
      printf("Loi mo file!\n");   
      exit(EXIT_FAILURE);             // thoát chương trình nếu có lỗi mở file
   }
   char tmp[50];
   fgets(tmp, 50, fptr); // đọc 1 dòng
   n = atoi(tmp); // chuyển chuỗi về số, dòng đầu tiên là số lượng cuốn sách.
   // Kiểm tra số món ăn trong file ko đc vượt qua MAX_SIZE, cũng ko được âm
   if (n < 0 || n > MAX_SIZE){
       printf("So luong cuon sach khong hop le!");
       exit(EXIT_FAILURE);
   }
   for (int i = 0; i < n; i++){
        // đọc 8 dòng để lấy thông tin 1 cuốn sách
        fgets(b[i].maBook, 50, fptr);
        b[i].maBook[strcspn(b[i].maBook, "\n")] = 0; // xóa \n ở cuối
        fgets(b[i].tenBook, 50, fptr);
        b[i].tenBook[strcspn(b[i].tenBook, "\n")] = 0;
        fgets(b[i].tacGia, 50, fptr);
        b[i].tacGia[strcspn(b[i].tacGia, "\n")] = 0;
        fgets(b[i].nhaXB, 50, fptr);
        b[i].nhaXB[strcspn(b[i].nhaXB, "\n")] = 0;
        fgets(tmp, 50, fptr);
        b[i].namXB = atoi(tmp);
        fgets(tmp, 50, fptr);
        b[i].donGia = atof(tmp);
        fgets(tmp, 50, fptr);
        b[i].soLuong = atoi(tmp);
        fgets(tmp, 50, fptr);
        b[i].thueVAT = atof(tmp);
        b[i].thanhTien = b[i].donGia * b[i].soLuong;
        b[i].thucTien = (1 + b[i].thueVAT) * b[i].thanhTien;
   }
   printf("Doc %d cuon sach tu %s thanh cong!\n", n, DATA_PATH);
    fclose(fptr);
}

// Hàm in menu 
void InMenu(){
    cout <<"=================== MENU ======================\n";
    cout << "1. Nhap sach tu ban phim\n";
    cout << "2. Hien thi thong tin cac cuon sach\n";
    cout << "3. Tinh cot thanh tien\n";
    cout << "4. Tinh cot thuc tien\n";
    cout << "5. Sap xep giam dan theo nam xb\n";
    cout << "6. Thong tin sach co thuc tien lon nhat\n";
    cout << "7. In thong tin tong so cac cuon sach\n";
    cout << "8. Loc danh sach theo thue VAT\n";
    cout << "9. Luu ra tep\n";
    cout << "10. Doc tu tep\n";
    cout << "0. Thoat\nLua chon cua ban: ";
}

int main(){
    int n = 0, luaChon;
    Book books[MAX_SIZE];
    while (1){
        InMenu();
        cin >> luaChon;
        switch (luaChon)
        {
        case 1:
            cout << "Nhap so luong book: ";
            cin >> n;
            if (n <= 0 || n > MAX_SIZE){
                cout << "Vui long nhap n trong pham vi 1-100!\n";
                continue;
            }
            NhapBooks(books, n);
            break;
        case 2:
            XuatBooks(books, n);
            break;
        case 3:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            TinhThanhTien(books, n);
            break;
        case 4:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            if (books[0].thanhTien == 0){
                cout << "Vui long tinh thanh tien truoc!";
                continue;
            }
            TinhThucTien(books, n);
            break;
        case 5:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            SapXep(books, n);
            break;
        case 6:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            MaxSach(books, n);
            break;
        case 7:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            TongSoCuonSach(books, n);
            break;
        case 8:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            LocTheoVAT(books, n);
            break;
        case 9:
            if (n == 0){
                cout << "Vui long nhap du lieu truoc!";
                continue;
            }
            toFile(books, n);
            break;
        case 10:
            fromFile(books, n);
            XuatBooks(books, n);
            break;
        case 0:
            cout << "Tam biet!\n";
            exit(0);
        default:
            cout << "Vui long lua chon cac chuc nang tu 0 - 10!\n";
            continue;
        }
    }
}
