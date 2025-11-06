# 🎯 HƯỚNG DẪN SỬ DỤNG F5 BUILD & RUN

## ✅ ĐÃ CẤU HÌNH

Tôi đã tạo 3 files cấu hình trong thư mục `.vscode/`:

1. **`tasks.json`** - Cấu hình build tự động với g++
2. **`launch.json`** - Cấu hình chạy trong terminal bên ngoài
3. **`settings.json`** - Cấu hình môi trường C++

---

## 🚀 CÁCH SỬ DỤNG

### Cách 1: Chạy file hiện tại (main.cpp, test_book.cpp, v.v.)

1. Mở file `.cpp` bất kỳ (ví dụ: `main.cpp` hoặc `test_book.cpp`)
2. **Nhấn F5** hoặc **Run > Start Debugging**
3. Chương trình sẽ:
   - ✅ Tự động build với g++
   - ✅ Link với `src/Book.cpp`
   - ✅ Chạy trong **terminal bên ngoài** (External Console)
   - ✅ Hiện giao diện như IDE C/C++ chuẩn

### Cách 2: Chạy main.cpp cụ thể

1. Nhấn **F5**
2. Chọn **"Run main.cpp in External Terminal"**
3. Chương trình sẽ build và chạy `library.exe`

---

## 🎨 TÍNH NĂNG

### ✅ Auto Build
- Mỗi lần nhấn F5 sẽ tự động build lại
- Không cần gõ lệnh `g++` thủ công
- Hiển thị lỗi compile (nếu có) trong Problems panel

### ✅ External Terminal
- Chạy trong cửa sổ CMD/PowerShell riêng
- Giống như IDE C/C++ Dev-C++, Code::Blocks
- Có thể nhập input từ bàn phím
- Cửa sổ không tự đóng sau khi chạy xong

### ✅ Include Path
- Tự động nhận `include/` folder
- IntelliSense hoạt động tốt
- Auto-complete cho Book.h, Reader.h, v.v.

---

## 📋 CHI TIẾT CẤU HÌNH

### 1. tasks.json - Build Task

```json
{
    "label": "C++: g++ build active file",
    "command": "g++",
    "args": [
        "-g",                                      // Debug symbols
        "${file}",                                 // File hiện tại
        "${workspaceFolder}\\src\\Book.cpp",      // Link Book.cpp
        "-I", "${workspaceFolder}\\include",      // Include path
        "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"
    ]
}
```

**Giải thích:**
- `-g`: Thêm debug symbols
- `${file}`: File đang mở (main.cpp, test_book.cpp)
- `src\\Book.cpp`: Link với Book module
- `-I include`: Thêm include path
- `-o`: Output file name

### 2. launch.json - Run Configuration

```json
{
    "name": "C++: Run in External Terminal",
    "type": "cppdbg",
    "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
    "externalConsole": true,              // ⭐ Chạy terminal bên ngoài
    "preLaunchTask": "C++: g++ build active file"  // Build trước khi chạy
}
```

**Giải thích:**
- `externalConsole: true`: Mở cửa sổ terminal riêng
- `preLaunchTask`: Tự động build trước khi chạy
- `MIMode: gdb`: Dùng GDB debugger

### 3. settings.json - VS Code Settings

```json
{
    "C_Cpp.default.includePath": ["${workspaceFolder}/include"],
    "C_Cpp.default.compilerPath": "g++.exe",
    "C_Cpp.default.cppStandard": "c++17"
}
```

**Giải thích:**
- IntelliSense biết `include/` path
- Sử dụng g++ compiler
- C++17 standard

---

## 🎯 DEMO

### Test với main.cpp:

1. Mở file `main.cpp`
2. Nhấn **F5**
3. Terminal bên ngoài sẽ mở và hiện:

```
Dang tai du lieu...
Doc file thanh cong! Tong so sach: 5

============================================
       QUAN LY SACH THU VIEN
============================================
1. Them sach moi
2. Xoa sach
3. Hien thi danh sach sach
...
```

### Test với test_book.cpp:

1. Mở file `test_book.cpp`
2. Nhấn **F5**
3. Terminal bên ngoài sẽ chạy test:

```
===== DOC DU LIEU TU FILE =====
Them sach thanh cong! Ma sach: S001
...
===== TEST THEM SACH =====
...
```

---

## 🔧 TROUBLESHOOTING

### Lỗi: "g++ not found"

**Giải pháp:**
```powershell
# Kiểm tra g++ đã cài chưa
g++ --version

# Nếu chưa có, cài MinGW hoặc TDM-GCC
```

### Lỗi: "gdb not found"

**Giải pháp 1:** Thay `gdb.exe` bằng đường dẫn đầy đủ trong `launch.json`:
```json
"miDebuggerPath": "C:\\MinGW\\bin\\gdb.exe"
```

**Giải pháp 2:** Nếu không cần debug, có thể bỏ qua

### Terminal không mở bên ngoài

**Kiểm tra:**
```json
"externalConsole": true  // Phải là true
```

### Build lỗi "Book.h not found"

**Kiểm tra:**
- File `include/Book.h` tồn tại
- Path trong `tasks.json` đúng: `-I ${workspaceFolder}\\include`

---

## 📝 NOTES

### Khi thêm module mới (Reader.cpp, BorrowSlip.cpp):

**Cập nhật tasks.json:**
```json
"args": [
    "-g",
    "${file}",
    "${workspaceFolder}\\src\\Book.cpp",
    "${workspaceFolder}\\src\\Reader.cpp",        // ⭐ Thêm dòng này
    "${workspaceFolder}\\src\\BorrowSlip.cpp",    // ⭐ Thêm dòng này
    "-I", "${workspaceFolder}\\include",
    "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"
]
```

### Để compile tất cả files trong src/:

**Thay đổi args thành:**
```json
"args": [
    "-g",
    "${file}",
    "${workspaceFolder}\\src\\*.cpp",  // ⭐ Compile tất cả .cpp trong src/
    "-I", "${workspaceFolder}\\include",
    "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"
]
```

---

## 🎮 SHORTCUTS

| Phím tắt | Chức năng |
|----------|-----------|
| **F5** | Build & Run (External Terminal) |
| **Ctrl+F5** | Run Without Debugging |
| **Ctrl+Shift+B** | Build Only (không chạy) |
| **Shift+F5** | Stop Debugging |

---

## ✅ CHECKLIST

- [x] `tasks.json` - Build configuration
- [x] `launch.json` - Run configuration
- [x] `settings.json` - IDE settings
- [x] External Console enabled
- [x] Auto build on F5
- [x] Include path configured
- [x] IntelliSense working

---

## 🎊 HOÀN TẤT!

Bây giờ bạn có thể:
1. ✅ Nhấn **F5** để build & run
2. ✅ Terminal mở bên ngoài như IDE C++ chuẩn
3. ✅ Tự động build mỗi lần F5
4. ✅ IntelliSense hoạt động tốt
5. ✅ Debug với breakpoints (nếu cần)

**Chúc bạn code vui vẻ! 🚀**

---

**Updated:** 06/11/2025  
**Status:** ✅ Ready to use
