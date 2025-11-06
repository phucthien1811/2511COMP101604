# 🚀 QUICK REFERENCE - QUẢN LÝ SÁCH

## ⚡ Biên dịch & Chạy

```powershell
# Biên dịch
g++ -o library.exe main.cpp src/Book.cpp -I include

# Chạy
.\library.exe
```

## 📋 Cấu trúc Book

```cpp
struct Book {
    string maSach;         // Mã sách (unique)
    string tenSach;        // Tên sách
    string tacGia;         // Tác giả
    string nhaXuatBan;     // Nhà xuất bản
    int namPhatHanh;       // Năm (1000 - hiện tại)
    int soTrang;           // Số trang (> 0)
    string ngayNhap;       // DD/MM/YYYY
    int tinhTrang;         // 1=Còn, 0=Đang mượn
};
```

## 🎯 API Chính

### BookList Methods

```cpp
// Thêm sách (kiểm tra trùng mã)
bool themSach(const Book& sach);

// Xóa sách (KHÔNG xóa nếu đang mượn)
bool xoaSach(const string& maSach);

// Hiển thị toàn bộ
void hienThiDanhSach();

// Tìm theo mã
Book* timSach(const string& maSach);

// Tìm theo tên
void timKiemTheoTen(const string& ten);

// Tìm theo tác giả
void timKiemTheoTacGia(const string& tacGia);

// File I/O
bool docTuFile(const string& filename);
bool luuVaoFile(const string& filename);

// Cập nhật tình trạng
bool capNhatTinhTrang(const string& maSach, int tinhTrangMoi);

// Kiểm tra
bool sachDangDuocMuon(const string& maSach);
```

## 📄 Format File SACH.txt

```
MaSach|TenSach|TacGia|NhaXuatBan|NamPH|SoTrang|NgayNhap|TinhTrang
```

**Ví dụ:**
```
S001|Lap trinh C++|Nguyen Van A|NXB Giao duc|2020|350|01/01/2024|1
S002|Cau truc du lieu|Tran Thi B|NXB Khoa hoc|2019|450|15/02/2024|0
```

## 🔒 Quy tắc bảo vệ

```cpp
// ❌ KHÔNG cho thêm mã trùng
if (kiemTraMaSachTonTai(maSach)) {
    return false;
}

// ❌ KHÔNG cho xóa sách đang mượn
if (node->data.tinhTrang == 0) {
    return false;
}
```

## ✅ Validation

```cpp
// Năm: 1000 - năm hiện tại
bool kiemTraNamHopLe(int nam);

// Ngày: DD/MM/YYYY
bool kiemTraNgayHopLe(const string& ngay);

// Số trang > 0
if (sach.soTrang <= 0) return false;
```

## 🔗 Tích hợp module khác

### Với BorrowSlip (Mượn/Trả sách)

```cpp
// Khi mượn
bookList.capNhatTinhTrang(maSach, 0);

// Khi trả
bookList.capNhatTinhTrang(maSach, 1);

// Kiểm tra trước khi mượn
if (bookList.sachDangDuocMuon(maSach)) {
    cout << "Sach dang duoc muon!";
}
```

### Với Reader (Độc giả)

```cpp
// Kiểm tra sách có sẵn
Book* sach = bookList.timSach(maSach);
if (sach && sach->tinhTrang == 1) {
    // Cho phép mượn
} else {
    // Không cho mượn
}
```

## 🧪 Test Cases

```cpp
// Test 1: Thêm sách
Book s;
s.maSach = "S999";
s.tenSach = "Test";
s.tinhTrang = 1;
bookList.themSach(s);  // ✅ Thành công

// Test 2: Thêm trùng
bookList.themSach(s);  // ❌ Lỗi: mã đã tồn tại

// Test 3: Xóa sách đang mượn
bookList.xoaSach("S003");  // ❌ Lỗi: đang mượn

// Test 4: Xóa sách còn lại
bookList.xoaSach("S001");  // ✅ Thành công

// Test 5: Tìm sách
Book* found = bookList.timSach("S001");
if (found) { /* Tìm thấy */ }
```

## 📊 Độ phức tạp

| Thao tác | Time Complexity |
|----------|-----------------|
| Thêm | O(n) |
| Xóa | O(n) |
| Tìm | O(n) |
| Hiển thị | O(n) |

## 🎨 Menu

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

## 🐛 Troubleshooting

### Lỗi: "Khong the mo file"
```
✅ Kiểm tra thư mục data/ tồn tại
✅ Kiểm tra file SACH.txt tồn tại
```

### Lỗi: "Ma sach da ton tai"
```
✅ Dùng mã sách khác
✅ Kiểm tra file SACH.txt
```

### Lỗi: "Khong the xoa sach ... vi sach dang duoc muon"
```
✅ Đợi sách được trả (tinhTrang = 1)
✅ Hoặc thay đổi tinhTrang trong file
```

## 📁 Files cần có

```
LibraryProject/
├── include/
│   └── Book.h              ✅
├── src/
│   └── Book.cpp            ✅
├── data/
│   └── SACH.txt            ✅
├── main.cpp                ✅
└── library.exe             (sau khi compile)
```

## 💡 Tips

1. **Luôn kiểm tra tinhTrang trước khi xóa**
2. **Tự động lưu file sau mỗi thao tác quan trọng**
3. **Validate dữ liệu trước khi thêm**
4. **Sử dụng mã sách có format chuẩn (S001, S002...)**
5. **Ngày nhập format: DD/MM/YYYY**

## 📞 Support

**Files tài liệu:**
- `BOOK_MODULE_GUIDE.md` - Hướng dẫn chi tiết
- `BOOK_COMPLETION_REPORT.md` - Báo cáo hoàn thành
- `README.md` - Tổng quan dự án

---

**Version:** 1.0  
**Last Updated:** 06/11/2025  
**Status:** ✅ Production Ready
