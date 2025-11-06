# Hệ thống quản lý thư viện

## Mô tả dự án
Đây là dự án quản lý thư viện được viết bằng C++, sử dụng cấu trúc dữ liệu và giải thuật.

## Thư mụmục quản lí 
II. Phân chia nhiệm vụ
1. Quản lý quyền đăng nhập và truy cập hệ thống

File: Account.h, Account.cpp
Người thực hiện: (ghi tên)
Nội dung công việc:

Xử lý đăng nhập (username, password)

Mã hóa password bằng dấu * khi nhập

Đọc/ghi dữ liệu từ ACCOUNT.txt

Giới hạn đăng nhập sai tối đa 3 lần

Phân quyền truy cập (Admin / Nhân viên)

Sau khi đăng nhập thành công → vào menu chính

2. Quản lý sách ✅ HOÀN THÀNH

File: Book.h, Book.cpp
Người thực hiện: [Ghi tên của bạn]
Nội dung công việc:

✅ Thêm, xóa, hiển thị danh sách sách

✅ Thuộc tính: Mã sách, Tên sách, Tác giả, Nhà xuất bản, Năm phát hành, Số trang, Ngày nhập, Tình trạng

✅ Tình trạng: 1 = còn trong thư viện, 0 = đang được mượn

✅ Cập nhật và lưu dữ liệu vào SACH.txt

✅ Không cho xóa sách nếu đang được mượn

**Cấu trúc dữ liệu:** Danh sách liên kết đôi (Doubly Linked List)
**Các chức năng bổ sung:** 
- Tìm kiếm theo mã, tên, tác giả
- Kiểm tra tính hợp lệ của dữ liệu nhập (năm phát hành, ngày nhập, số trang)
- Tự động lưu file sau mỗi thao tác thêm/xóa

3. Quản lý bạn đọc

File: Reader.h, Reader.cpp
Người thực hiện: (ghi tên)
Nội dung công việc:

Thêm, sửa, xóa, hiển thị danh sách bạn đọc

Thuộc tính: Mã bạn đọc, Họ tên, Ngày sinh, Địa chỉ, Số điện thoại

Mỗi bạn đọc có mã duy nhất

Dữ liệu lưu trong DOCGIA.txt

4. Quản lý phiếu mượn – trả

File: BorrowSlip.h, BorrowSlip.cpp
Người thực hiện: (ghi tên)
Nội dung công việc:

Tạo phiếu mượn mới, hiển thị danh sách phiếu mượn

Thuộc tính: Số phiếu, Mã sách, Mã bạn đọc, Ngày mượn, Ngày phải trả, Tình trạng

Tự động tính ngày phải trả = ngày mượn + 7

Khi trả sách: cập nhật tình trạng phiếu = 0, tình trạng sách = 1

Ghi đè dữ liệu vào PHIEUMUON.txt và SACH.txt

5. Giao diện menu và xử lý tiện ích chung

File: Menu.h, Menu.cpp, Utils.h, Utils.cpp
Người thực hiện: (ghi tên)
Nội dung công việc:

Hiển thị menu chính và menu con:

1. Quản lý Sách
2. Quản lý Bạn đọc
3. Quản lý Phiếu mượn
4. Thoát


Điều hướng gọi các module tương ứng

Viết các hàm tiện ích dùng chung: xử lý chuỗi, ngày tháng, căn lề, tạm dừng màn hình

Làm việc cùng main.cpp để kết nối toàn bộ chương trình

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
