# Hệ thống quản lý thư viện

## Mô tả dự án
Đây là dự án quản lý thư viện được viết bằng C++, sử dụng cấu trúc dữ liệu và giải thuật.

## Cấu trúc thư mục

```
LibraryProject/
│
├── main.cpp                   # Điểm vào chương trình
│
├── include/                   # Thư mục chứa file header (.h)
│   ├── Book.h                 # Khai báo class Book
│   ├── Reader.h               # Khai báo class Reader
│   ├── BorrowSlip.h           # Khai báo class BorrowSlip
│   ├── Account.h              # Khai báo class Account (đăng nhập)
│   ├── Menu.h                 # Các hàm hiển thị menu, giao diện CLI
│   └── Utils.h                # Hàm tiện ích: xử lý file, format, validate
│
├── src/                       # Thư mục chứa file cài đặt (.cpp)
│   ├── Book.cpp               # Cài đặt class Book
│   ├── Reader.cpp             # Cài đặt class Reader
│   ├── BorrowSlip.cpp         # Cài đặt class BorrowSlip
│   ├── Account.cpp            # Cài đặt class Account
│   ├── Menu.cpp               # Cài đặt các hàm menu
│   └── Utils.cpp              # Cài đặt hàm tiện ích
│
├── data/                      # Lưu file dữ liệu
│   ├── SACH.txt
│   ├── DOCGIA.txt
│   ├── PHIEUMUON.txt
│   └── ACCOUNT.txt
│
└── README.md
```

## Chức năng chính

1. **Quản lý sách**
   - Thêm, xóa, sửa thông tin sách
   - Hiển thị danh sách sách

2. **Quản lý độc giả**
   - Thêm, xóa, sửa thông tin độc giả
   - Hiển thị danh sách độc giả

3. **Quản lý phiếu mượn**
   - Tạo phiếu mượn sách
   - Trả sách
   - Hiển thị danh sách phiếu mượn

4. **Tìm kiếm**
   - Tìm sách theo mã, tên
   - Tìm độc giả theo mã, tên

5. **Đăng nhập**
   - Hệ thống tài khoản admin và user

## Hướng dẫn biên dịch

### Windows (MinGW/g++)
```bash
g++ -o library main.cpp src/*.cpp -I include
```

### Linux/Mac
```bash
g++ -o library main.cpp src/*.cpp -I include
./library
```

## Tài khoản mặc định
- Admin: username=`admin`, password=`admin123`
- User: username=`user`, password=`user123`

## Yêu cầu
- Compiler C++ hỗ trợ C++11 trở lên
- MinGW hoặc GCC

## Tác giả
Dự án được phát triển cho môn Cấu trúc dữ liệu và giải thuật
