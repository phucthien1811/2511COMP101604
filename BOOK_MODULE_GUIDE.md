# HƯỚNG DẪN MODULE QUẢN LÝ SÁCH

## 📚 Tổng quan

Module quản lý sách được thiết kế để xử lý toàn bộ các nghiệp vụ liên quan đến sách trong hệ thống thư viện.

**Người thực hiện:** [Ghi tên của bạn]  
**Ngày hoàn thành:** 06/11/2025  
**Trạng thái:** ✅ HOÀN THÀNH

---

## 🎯 Chức năng đã thực hiện

### 1. Thêm sách (✅)
- Nhập đầy đủ thông tin sách
- Kiểm tra mã sách trùng lặp
- Validate dữ liệu nhập (năm, ngày, số trang)
- Tự động lưu vào file

### 2. Xóa sách (✅)
- Tìm sách theo mã
- **Kiểm tra bảo vệ**: Không cho xóa sách đang được mượn
- Xóa khỏi danh sách liên kết
- Cập nhật file

### 3. Hiển thị danh sách (✅)
- Hiển thị toàn bộ sách dạng bảng
- Format đẹp, dễ đọc
- Hiển thị số lượng sách

### 4. Tìm kiếm (✅)
- Tìm theo mã sách
- Tìm theo tên sách
- Tìm theo tác giả

### 5. Quản lý file (✅)
- Đọc dữ liệu từ SACH.txt
- Lưu dữ liệu vào SACH.txt
- Format: `MaSach|TenSach|TacGia|NhaXuatBan|Nam|SoTrang|NgayNhap|TinhTrang`

---

## 📋 Thuộc tính sách

```cpp
struct Book {
    string maSach;        // Mã sách (unique)
    string tenSach;       // Tên sách
    string tacGia;        // Tác giả
    string nhaXuatBan;    // Nhà xuất bản
    int namPhatHanh;      // Năm phát hành (1000 - năm hiện tại)
    int soTrang;          // Số trang (> 0)
    string ngayNhap;      // Ngày nhập (DD/MM/YYYY)
    int tinhTrang;        // 1 = Còn, 0 = Đang mượn
};
```

---

## 🔧 Cấu trúc dữ liệu

### Danh sách liên kết đôi (Doubly Linked List)

```
   [NULL] <- [Book1] <-> [Book2] <-> [Book3] -> [NULL]
              ↑                                    ↑
             head                                tail
```

**Ưu điểm:**
- Thêm/xóa hiệu quả: O(1) khi có con trỏ
- Duyệt 2 chiều
- Quản lý bộ nhớ linh hoạt

---

## 🚀 Hướng dẫn biên dịch và chạy

### Windows (PowerShell)

```powershell
# 1. Di chuyển vào thư mục dự án
cd D:\HP\201_CTDL\LibraryProject

# 2. Biên dịch
g++ -o library.exe main.cpp src/Book.cpp -I include

# 3. Chạy
.\library.exe
```

### Linux/Mac

```bash
# 1. Di chuyển vào thư mục dự án
cd ~/LibraryProject

# 2. Biên dịch
g++ -o library main.cpp src/Book.cpp -I include

# 3. Chạy
./library
```

---

## 📝 Format dữ liệu SACH.txt

### Cấu trúc
```
MaSach|TenSach|TacGia|NhaXuatBan|NamPhatHanh|SoTrang|NgayNhap|TinhTrang
```

### Ví dụ
```
S001|Lap trinh C++ co ban|Nguyen Van A|NXB Giao duc|2020|350|01/01/2024|1
S002|Cau truc du lieu va giai thuat|Tran Thi B|NXB Khoa hoc|2019|450|15/02/2024|1
S003|Tri tue nhan tao|Le Van C|NXB Tre|2021|500|20/03/2024|0
```

### Ý nghĩa tình trạng
- `1` = Còn trong thư viện (có thể mượn)
- `0` = Đang được mượn (không thể xóa)

---

## 💻 Sử dụng chương trình

### Menu chính

```
============================================
       QUAN LY SACH THU VIEN
============================================
1. Them sach moi
2. Xoa sach
3. Hien thi danh sach sach
4. Tim sach theo ma
5. Tim sach theo ten
6. Tim sach theo tac gia
7. Doc du lieu tu file
8. Luu du lieu vao file
0. Thoat
============================================
```

### 1️⃣ Thêm sách mới

**Bước thực hiện:**
```
Chọn: 1
Ma sach: S006
Ten sach: Lap trinh Python
Tac gia: John Doe
Nha xuat ban: NXB Thong tin
Nam phat hanh: 2023
So trang: 400
Ngay nhap (DD/MM/YYYY): 06/11/2025
```

**Kết quả:**
```
Them sach thanh cong! Ma sach: S006
Luu file thanh cong!
```

### 2️⃣ Xóa sách

**Trường hợp 1: Xóa sách đang được mượn (BỊ TỪ CHỐI)**
```
Chọn: 2
Nhap ma sach can xoa: S003
Loi: Khong the xoa sach 'S003' vi sach dang duoc muon!
```

**Trường hợp 2: Xóa sách còn trong thư viện (THÀNH CÔNG)**
```
Chọn: 2
Nhap ma sach can xoa: S001
Xoa sach thanh cong! Ma sach: S001
Luu file thanh cong!
```

### 3️⃣ Hiển thị danh sách

```
========== DANH SACH SACH ==========
Tong so sach: 5
------------------------------------------------------------------
Ma sach     Ten sach                      Tac gia            ...
------------------------------------------------------------------
S001        Lap trinh C++ co ban          Nguyen Van A       ...
S002        Cau truc du lieu va giai thu  Tran Thi B         ...
------------------------------------------------------------------
```

### 4️⃣ Tìm sách theo mã

```
Chọn: 4
Nhap ma sach can tim: S001

========== THONG TIN SACH ==========
Ma sach: S001
Ten sach: Lap trinh C++ co ban
Tac gia: Nguyen Van A
Nha xuat ban: NXB Giao duc
Nam phat hanh: 2020
So trang: 350
Ngay nhap: 01/01/2024
Tinh trang: Con trong thu vien
====================================
```

### 5️⃣ Tìm sách theo tên

```
Chọn: 5
Nhap ten sach can tim: C++

========== KET QUA TIM KIEM THEO TEN ==========
(Hiển thị tất cả sách có chứa từ "C++" trong tên)
```

### 6️⃣ Tìm sách theo tác giả

```
Chọn: 6
Nhap ten tac gia can tim: Nguyen

========== KET QUA TIM KIEM THEO TAC GIA ==========
(Hiển thị tất cả sách của tác giả có chứa "Nguyen")
```

---

## ⚙️ API Reference

### Class: `BookList`

#### Constructor & Destructor
```cpp
BookList();              // Khởi tạo danh sách rỗng
~BookList();             // Giải phóng bộ nhớ
```

#### Quản lý sách
```cpp
bool themSach(const Book& sach);
// Thêm sách mới vào danh sách
// Return: true nếu thành công, false nếu mã sách đã tồn tại

bool xoaSach(const string& maSach);
// Xóa sách khỏi danh sách
// Return: true nếu thành công, false nếu không tìm thấy hoặc đang được mượn

void hienThiDanhSach();
// Hiển thị toàn bộ danh sách sách dạng bảng

Book* timSach(const string& maSach);
// Tìm sách theo mã
// Return: con trỏ đến Book nếu tìm thấy, nullptr nếu không
```

#### Quản lý file
```cpp
bool docTuFile(const string& filename);
// Đọc dữ liệu từ file
// Return: true nếu thành công

bool luuVaoFile(const string& filename);
// Lưu dữ liệu vào file
// Return: true nếu thành công
```

#### Cập nhật tình trạng
```cpp
bool capNhatTinhTrang(const string& maSach, int tinhTrangMoi);
// Cập nhật tình trạng sách (0 hoặc 1)
// Return: true nếu thành công

bool sachDangDuocMuon(const string& maSach);
// Kiểm tra sách có đang được mượn không
// Return: true nếu đang được mượn
```

#### Tìm kiếm
```cpp
void timKiemTheoTen(const string& ten);
// Tìm và hiển thị sách có tên chứa từ khóa

void timKiemTheoTacGia(const string& tacGia);
// Tìm và hiển thị sách của tác giả có tên chứa từ khóa
```

#### Utility
```cpp
int laySoLuong() const;
// Lấy số lượng sách hiện tại trong danh sách
```

### Helper Functions

```cpp
void nhapThongTinSach(Book& sach);
// Nhập thông tin sách từ bàn phím với validation

bool kiemTraNamHopLe(int nam);
// Kiểm tra năm trong khoảng 1000 - năm hiện tại

bool kiemTraNgayHopLe(const string& ngay);
// Kiểm tra ngày hợp lệ theo format DD/MM/YYYY
```

---

## 🔒 Các quy tắc bảo vệ dữ liệu

### 1. Mã sách duy nhất
- ❌ Không cho thêm sách có mã trùng lặp
- ✅ Kiểm tra trước khi thêm

### 2. Không xóa sách đang mượn
- ❌ Không cho xóa khi `tinhTrang = 0`
- ✅ Hiển thị thông báo lỗi rõ ràng

### 3. Validation dữ liệu nhập
- **Năm phát hành**: 1000 ≤ năm ≤ năm hiện tại
- **Số trang**: > 0
- **Ngày nhập**: đúng format DD/MM/YYYY và hợp lệ

---

## 🔗 Tích hợp với module khác

### 1. Với BorrowSlip (Phiếu mượn)
```cpp
// Khi mượn sách
bookList.capNhatTinhTrang(maSach, 0);  // Đánh dấu đang mượn

// Khi trả sách
bookList.capNhatTinhTrang(maSach, 1);  // Đánh dấu còn lại
```

### 2. Với Reader (Độc giả)
```cpp
// Kiểm tra sách có sẵn để mượn
Book* sach = bookList.timSach(maSach);
if (sach && sach->tinhTrang == 1) {
    // Cho phép mượn
}
```

### 3. Với Menu
```cpp
// Gọi từ menu chính
void menuQuanLySach(BookList& danhSachSach) {
    // Xử lý các lựa chọn menu
}
```

---

## 🐛 Xử lý lỗi

### Lỗi thường gặp và cách khắc phục

**1. Không đọc được file**
```
Khong the mo file: data/SACH.txt
```
✅ **Giải pháp**: Kiểm tra thư mục `data/` đã tồn tại chưa

**2. Mã sách trùng**
```
Loi: Ma sach 'S001' da ton tai!
```
✅ **Giải pháp**: Dùng mã sách khác

**3. Xóa sách đang mượn**
```
Loi: Khong the xoa sach 'S003' vi sach dang duoc muon!
```
✅ **Giải pháp**: Đợi sách được trả rồi mới xóa

**4. Năm không hợp lệ**
```
Nam phat hanh khong hop le! Vui long nhap lai.
```
✅ **Giải pháp**: Nhập năm từ 1000 đến năm hiện tại

**5. Ngày không hợp lệ**
```
Ngay khong hop le! Vui long nhap theo dinh dang DD/MM/YYYY.
```
✅ **Giải pháp**: Nhập đúng format DD/MM/YYYY (ví dụ: 06/11/2025)

---

## 📊 Độ phức tạp thuật toán

| Thao tác | Độ phức tạp | Ghi chú |
|----------|-------------|---------|
| Thêm sách | O(n) | Kiểm tra trùng lặp + thêm cuối |
| Xóa sách | O(n) | Tìm kiếm + xóa |
| Tìm sách | O(n) | Duyệt tuần tự |
| Hiển thị | O(n) | Duyệt toàn bộ |
| Đọc file | O(n) | n = số dòng |
| Lưu file | O(n) | n = số sách |

---

## 🧪 Test Cases

### Test 1: Thêm sách thành công
```
Input: Mã mới, thông tin hợp lệ
Expected: "Them sach thanh cong!"
```

### Test 2: Thêm sách trùng mã
```
Input: Mã đã tồn tại
Expected: "Loi: Ma sach ... da ton tai!"
```

### Test 3: Xóa sách đang mượn
```
Input: Mã sách có tinhTrang = 0
Expected: "Loi: Khong the xoa sach ... vi sach dang duoc muon!"
```

### Test 4: Xóa sách thành công
```
Input: Mã sách có tinhTrang = 1
Expected: "Xoa sach thanh cong!"
```

### Test 5: Tìm sách tồn tại
```
Input: Mã sách hợp lệ
Expected: Hiển thị thông tin sách
```

### Test 6: Tìm sách không tồn tại
```
Input: Mã sách không có
Expected: "Khong tim thay sach..."
```

---

## 📚 Tài liệu tham khảo

1. **Doubly Linked List**: [GeeksforGeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
2. **File I/O in C++**: [cplusplus.com](http://www.cplusplus.com/doc/tutorial/files/)
3. **String manipulation**: [cppreference.com](https://en.cppreference.com/w/cpp/string)

---

## ✅ Checklist hoàn thành

- [x] Định nghĩa struct Book với đầy đủ thuộc tính
- [x] Tạo cấu trúc Doubly Linked List
- [x] Implement thêm sách
- [x] Implement xóa sách với bảo vệ (không xóa khi đang mượn)
- [x] Implement hiển thị danh sách
- [x] Implement tìm kiếm (mã, tên, tác giả)
- [x] Implement đọc/ghi file
- [x] Validation dữ liệu nhập
- [x] Tự động lưu sau thao tác
- [x] Cập nhật tình trạng sách
- [x] Test toàn bộ chức năng
- [x] Viết documentation

---

## 👤 Thông tin liên hệ

**Người thực hiện:** [Ghi tên của bạn]  
**Email:** [Email của bạn]  
**Ngày hoàn thành:** 06/11/2025

---

## 📄 License

Dự án này được phát triển cho mục đích học tập - Môn Cấu trúc dữ liệu và Giải thuật.

---

**🎉 HOÀN THÀNH MODULE QUẢN LÝ SÁCH! 🎉**
