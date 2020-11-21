#include <iostream>
#include<string>	
#include<fstream>
#include<Windows.h>
#include<io.h>
#include<fcntl.h>
#include<locale>
#include<codecvt>
#define FILELO "AnhViet.txt"

using namespace std;

struct TUNGU {
	wstring goc;
	wstring nghia;
};

struct NODE {
	TUNGU info;
	NODE* pNext;
};
struct LINKEDLIST {
	NODE* pHead;
	NODE* pTail;
};
void AddFirst(LINKEDLIST& A, TUNGU word);
int Bash(wstring word);
void TuDien();



int main()
{
	TuDien();
	return 0;
}

int NhapFile(LINKEDLIST Dic[]) {
	wcout << L"Đang tải dữ liệu cho từ điển...." << endl;
	locale utf8loc(locale(), new codecvt_utf8<wchar_t>);
	fflush(stdin);
	wifstream infile;
	infile.open(FILELO);
	infile.imbue(utf8loc);
	if (!infile) {
		wcout << L"Đọc file thất bại." << endl;
		return 1;
	}
	else
	{
		TUNGU word;
		do {
			getline(infile, word.goc, L'\t');
			getline(infile, word.nghia, L'\n');
			int x = Bash(word.goc);
			if (x >= 0 && x <= 26) {
				AddFirst(Dic[x], word);
			}

		} while (!infile.eof());
		wcout << L"Đã tải dữ liệu xong" << endl;
	}
	infile.close();
	return 0;
}
NODE* CreateNode(TUNGU x)
{
	NODE* p = new NODE;
	p->info = x;
	p->pNext = NULL;
	return p;
}
void AddFirst(LINKEDLIST& A, TUNGU word)
{
	NODE* p = CreateNode(word);
	p->pNext = A.pHead;
	A.pHead = p;
}
void InitList(LINKEDLIST A[])
{
	for (int i = 0; i < 26; i++) {
		A[i].pHead = A[i].pTail = NULL;
	}
}
wstring TraTu(LINKEDLIST Dic[], wstring word)
{
	int x = Bash(word);
	for (NODE* p = Dic[x].pHead; p != NULL; p = p->pNext)
	{
		if (p->info.goc == word)
			return p->info.nghia;
	}
	return L"NULL";
}
int Bash(wstring word)
{
	return (int)word[0] - 97;
}


void ChuanHoa(wstring& word)
{
	if (word != L"")
	{
		//Xoa khoang trang dau
		while (isspace(word[0])) {
			word.erase(word.begin()); // XoaVTK(word, 0);
		}
		//Xoa khoang trang cuoi
		while (isspace(word[word.length() - 1])) {
			word.erase(word.length() - 1);
		}
		//Xoa khoang trang giua
		for (int i = 0; i < word.length(); i++) {
			if (isspace(word[i]) && isspace(word[i + 1]))
			{
				while (isspace(word[i + 1]))
				{
					word.erase(i, 1);
				}
			}
		}
		//To lower
		if (word != L"N")
		{
			for (int i = 0; i < word.length(); i++) {
				if (word[i] >= 65 && word[i] <= 90)
					word[i] += 32;
			}
		}
	}
}
int KiemTra(wstring word)
{
	if ((word[0] >= 65 && word[0] <= 90) || (word[0] >= 97 && word[0] <= 122))
		return 0;
	return 1;
}
void TuDien_TraTu(LINKEDLIST Dic[])
{
	system("cls");
	wcout << L"------------- Tra từ ------------" << endl;
	wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
	TUNGU input;
	int c = 0;
	do {
		wcout << L"Nhập từ bạn muốn tra:";
		getline(wcin, input.goc);
		ChuanHoa(input.goc);
		if (KiemTra(input.goc)) {
			system("cls");
			wcout << L"------------- Tra từ ------------" << endl;
			wcout << L"Có vẻ bạn đã nhập sai cú pháp, vui lòng kiểm tra lại." << endl;
			wcout << "------------------------------------------------------------------------------------------------------------------" << endl;
			wcout << L"Nếu bạn muốn tiếp tục hãy nhập từ cần tra." << endl;
			wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N' \n" << endl;
		}
		else
		{
			if (input.goc == L"N")
				c = 1;
			else
			{
				system("cls");
				wcout << L"------------- Tra từ ------------" << endl;
				wcout << L"Đang hiển thị kết quả cho";
				HANDLE hConsoleColor;
				hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsoleColor, 14);
				wcout << L"'" << input.goc << L"'\n" << endl;
				SetConsoleTextAttribute(hConsoleColor, 7);
				input.nghia = TraTu(Dic, input.goc);
				if (input.nghia != L"NULL") {
					wcout << input.nghia << endl;
					wcout << L"\n";
				}
				else {
					wcout << L"Có vẻ như không có từ cần tìm trong từ điển." << endl;
					wcout << L"Nếu bạn muốn bổ sung từ này vào từ điển vui lòng quay lại Bảng chọn chức năng và chọn Thêm từ mới.\n" << endl;
				}
				wcout << "------------------------------------------------------------------------------------------------------------------" << endl;
				wcout << L"Nếu bạn muốn tiếp tục hãy nhập từ cần tra." << endl;
				wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N' \n" << endl;
			}
		}
	} while (c == 0);
}
int SoSanh(wstring word1, wstring word2)
{
	int x = -1;
	for (int i = 0; i < word1.length(); i++)
	{
		if (word1[i] == word2[0]) {
			int d = 1;
			for (int j = 1; j < word2.length(); j++) {
				if (i + j < word1.length())//kiem tra de khong gap loi truy xuat
					if (word1[i + j] == word2[j])
						d++;
			}
			if (d == word2.length()) //có số từ trùng bằng số từ của word2
				return 1;
		}
	}
	return 0;
}
int TraTu2(LINKEDLIST Dic[], wstring word)
{
	int kq = 0;
	for (int i = 0; i < 26; i++)
	{
		for (NODE* p = Dic[i].pHead; p != NULL; p = p->pNext) {
			if (SoSanh(p->info.goc, word)) {
				kq = 1;
				wcout << p->info.goc << " - " << p->info.nghia << endl;
			}
		}
	}
	return kq;
}
void TuDien_TraTu2(LINKEDLIST Dic[])
{
	system("cls");
	wcout << L"------------- Tra từ (theo từng chữ) ------------" << endl;
	wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'" << endl;
	wcout << L"Bạn có thể xem tất cả các từ đang có trong từ điển bằng cách nhập bỏ trống và nhấn Enter\n" << endl;
	TUNGU input;
	int c = 0;
	do {
		wcout << L"Nhập từ bạn muốn tra:";
		getline(wcin, input.goc);
		ChuanHoa(input.goc);
		if (KiemTra(input.goc) && input.goc != L"") {
			system("cls");
			wcout << L"------------- Tra từ (theo từng chữ) ------------" << endl;
			wcout << L"Có vẻ bạn đã nhập sai cú pháp, vui lòng kiểm tra lại." << endl;
			wcout << "------------------------------------------------------------------------------------------------------------------" << endl;

			wcout << L"Nếu bạn muốn tiếp tục hãy nhập tiếp." << endl;
			wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N' \n" << endl;
		}
		else
		{
			if (input.goc == L"N")
				c = 1;
			else
			{
				if (input.goc == L"")
				{
					system("cls");
					wcout << L"------------- Tra từ (theo từng chữ) ------------" << endl;
					wcout << L"Tất cả các từ đang có trong từ điển:\n" << endl;
					for (int i = 0; i < 26; i++) {
						for (NODE* p = Dic[i].pHead; p != NULL; p = p->pNext) {
							wcout << p->info.goc << " - " << p->info.nghia << endl;
						}
					}
				}
				else
				{
					system("cls");
					wcout << L"------------- Tra từ (theo từng chữ) ------------" << endl;
					wcout << L"Đang hiển thị kết quả cho";
					HANDLE hConsoleColor;
					hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << L"'" << input.goc << L"'\n" << endl;
					SetConsoleTextAttribute(hConsoleColor, 7);
					int x = TraTu2(Dic, input.goc);
					if (x == 0) {
						wcout << L"Không tìm được từ nào phù hợp với '" << input.goc << "'.\n" << endl;
					}
				}
				wcout << "------------------------------------------------------------------------------------------------------------------" << endl;
				wcout << L"Nếu bạn muốn tiếp tục hãy nhập từ cần tra." << endl;
				wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N' \n" << endl;
			}
		}
	} while (c == 0);
}
int ThemTu(LINKEDLIST Dic[], TUNGU word)
{
	int x = Bash(word.goc);
	if (x >= 0 && x <= 26)
		AddFirst(Dic[x], word);
	locale utf8loc(locale(), new codecvt_utf8<wchar_t>);
	wofstream outfile;
	outfile.open(FILELO, ofstream::app);
	if (!outfile) {
		return 1;
	}
	else {
		outfile.imbue(utf8loc);
		outfile << word.goc << L"\t" << word.nghia << L"\n";
	}
	outfile.close();
	return 0;
}
void TuDien_ThemTu(LINKEDLIST Dic[])
{
	system("cls");
	wcout << L"--------- Thêm từ ----------" << endl;
	wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
	TUNGU input;
	int c = 0;
	do {
		wcout << L"Nhập từ bạn muốn thêm:";

		getline(wcin, input.goc);
		ChuanHoa(input.goc);
		if (KiemTra(input.goc)) {
			system("cls");
			wcout << L"----------------------- Thêm từ -----------------------" << endl;
			wcout << L"\nBạn đã nhập sai cú pháp, vui lòng kiểm tra lại." << endl;
			wcout << L"\n------------------------------------------------------------------------------" << endl;
			wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
			wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
		}
		else
		{
			if (input.goc == L"N")
				c = 1;
			else {
				input.nghia = TraTu(Dic, input.goc);
				if (input.nghia == L"NULL")
				{

					wcout << L"Hãy nhập nghĩa cho từ ";
					HANDLE hConsoleColor;
					hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << L"'" << input.goc << L"'";
					SetConsoleTextAttribute(hConsoleColor, 7);
					wcout << L" :" << endl;
					wcout << L"(Nếu muốn hủy thao tác hãy nhập 'no')" << endl;
					getline(wcin, input.nghia);
					if (input.nghia != L"no")
					{
						system("cls");
						wcout << L"----------------------- Thêm từ -----------------------" << endl;
						wcout << L"Bắt đầu thêm từ mới vào từ điển..." << endl;
						wcout << L"Từ: " << input.goc << endl;
						wcout << L"Nghĩa: " << input.nghia << endl;
						int x = ThemTu(Dic, input);
						if (x == 0)
							wcout << L"Đã thêm từ thành công." << endl;
						else
							wcout << L"Đã thêm từ thất bại. Vui lòng xem lại." << endl;
					}
					else
					{
						system("cls");
						wcout << L"----------------------- Thêm từ -----------------------" << endl;
						wcout << L"\nĐã dừng thao tác." << endl;
					}
				}
				else
				{
					system("cls");
					wcout << L"----------------------- Thêm từ -----------------------" << endl;
					wcout << L"Từ ";
					HANDLE hConsoleColor;
					hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << L"'" << input.goc << L"' ";
					SetConsoleTextAttribute(hConsoleColor, 7);
					wcout << L" đã có trong từ điển.\n" << endl;
				}
				wcout << L"\n------------------------------------------------------------------------------" << endl;
				wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
				wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;

			}
		}
	} while (c == 0);
}
int GhiFile(LINKEDLIST Dic[])
{
	locale utf8loc(locale(), new codecvt_utf8<wchar_t>);
	wofstream outfile;
	outfile.open(FILELO);
	if (!outfile) {
		return 1;
	}
	else {
		outfile.imbue(utf8loc);
		for (int i = 0; i < 26; i++)
		{
			for (NODE* p = Dic[i].pHead; p != NULL; p = p->pNext)
			{
				outfile << p->info.goc << "\t" << p->info.nghia << "\n";
			}
		}
	}
	outfile.close();
	return 0;
}
int SuaTu(LINKEDLIST Dic[], TUNGU word)
{
	int x = Bash(word.goc);
	if (x >= 0 && x <= 26) {
		for (NODE* p = Dic[x].pHead; p != NULL; p = p->pNext)
		{
			if (p->info.goc == word.goc) {
				p->info.nghia = word.nghia;
			}
		}
	}
	int kq = GhiFile(Dic);
	return kq;
}
int SuaTu2(LINKEDLIST Dic[], TUNGU word)
{
	int x = Bash(word.goc);
	if (x >= 0 && x <= 26) {
		for (NODE* p = Dic[x].pHead; p != NULL; p = p->pNext)
		{
			if (p->info.goc == word.goc) {
				p->info.nghia = p->info.nghia + L", " + word.nghia;
			}
		}
	}
	int kq = GhiFile(Dic);
	return kq;
}
int XoaTu(LINKEDLIST Dic[], TUNGU word)
{
	int x = Bash(word.goc);
	if (x >= 0 && x <= 26) {
		NODE* px = Dic[x].pHead;
		if (px->info.goc == word.goc)
		{
			Dic[x].pHead = Dic[x].pTail = NULL;
			delete px;
		}
		else
		{
			while (px->pNext->info.goc != word.goc)
				px = px->pNext;
			NODE* ptemp = px;
			px = px->pNext->pNext;
			delete ptemp;
		}
	}
	int kq = GhiFile(Dic);
	return kq;
}
void TuDien_SuaTu(LINKEDLIST Dic[]) {
	system("cls");
	wcout << L"---------------------- Sửa từ -------------------------" << endl;
	wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
	TUNGU input;
	int c = 0;
	do {
		wcout << L"Nhập từ bạn muốn thay đổi nghĩa:";

		getline(wcin, input.goc);
		ChuanHoa(input.goc);
		if (KiemTra(input.goc)) {
			system("cls");
			wcout << L"---------------------- Sửa từ -------------------------" << endl;
			wcout << L"\nBạn đã nhập sai cú pháp, vui lòng kiểm tra lại." << endl;
			wcout << L"\n------------------------------------------------------------------------------" << endl;
			wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
			wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
		}
		else
		{
			if (input.goc == L"N")
			{
				c = 1;
			}
			else
			{
				input.nghia = TraTu(Dic, input.goc);
				if (input.nghia != L"NULL") {
					HANDLE hConsoleColor;
					hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
					wcout << L"Từ ";
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << L"'" << input.goc << L"' ";
					SetConsoleTextAttribute(hConsoleColor, 7);
					wcout << L"đang có nghĩa : ";
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << input.nghia << endl;
					SetConsoleTextAttribute(hConsoleColor, 7);
					wcout << L"Bạn muốn:" << endl;
					wcout << L"1. Thay đổi nghĩa(sẽ thay thế nghĩa hiện tại)" << endl;
					wcout << L"2. Bổ sung nghĩa" << endl;
					wcout << L"3. Xóa bỏ từ" << endl;
					wcout << L"0. Hủy thao tác" << endl;
					int x = -1;
					wstring check;
					getline(wcin, check);
					ChuanHoa(check);
					while (check != L"1" && check != L"2" && check != L"3" && check != L"0") {
						system("cls");
						wcout << L"---------------------- Sửa từ -------------------------\n" << endl;
						wcout << L"Từ ";
						SetConsoleTextAttribute(hConsoleColor, 14);
						wcout << L"'" << input.goc << L"' ";
						SetConsoleTextAttribute(hConsoleColor, 7);
						wcout << L"đang có nghĩa : ";
						SetConsoleTextAttribute(hConsoleColor, 14);
						wcout << input.nghia << endl;
						SetConsoleTextAttribute(hConsoleColor, 7);
						wcout << L"\nBạn muốn:" << endl;
						wcout << L"1. Thay đổi nghĩa(sẽ thay thế nghĩa hiện tại)" << endl;
						wcout << L"2. Bổ sung nghĩa" << endl;
						wcout << L"3. Xóa bỏ từ" << endl;
						wcout << L"0. Hủy thao tác" << endl;
						wcout << L"\nBạn đã nhập sai cú pháp. Vui lòng nhập lại." << endl;
						getline(wcin, check);
					}
					if (check == L"1")
					{
						wcout << L"Hãy nhập nghĩa bạn muốn sửa cho từ";
						SetConsoleTextAttribute(hConsoleColor, 14);
						wcout << L"'" << input.goc << L"' ";
						SetConsoleTextAttribute(hConsoleColor, 7);
						wcout << L":" << endl;
						wcout << L"(Nếu muốn hủy thao tác hãy nhập 'no')" << endl;
						getline(wcin, input.nghia);
						if (input.nghia != L"no")
						{
							system("cls");
							wcout << L"---------------------- Sửa từ -------------------------" << endl;
							wcout << L"Từ: " << input.goc << endl;
							wcout << L"Nghĩa: " << input.nghia << endl;
							x = SuaTu(Dic, input);
						}
					}
					else
					{
						if (check == L"2")
						{
							wcout << L"Hãy nhập nghĩa bạn muốn bổ sung cho từ";
							SetConsoleTextAttribute(hConsoleColor, 14);
							wcout << L"'" << input.goc << L"' " << endl;;
							SetConsoleTextAttribute(hConsoleColor, 7);
							wcout << L"(Nếu muốn hủy thao tác hãy nhập 'no')" << endl;
							getline(wcin, input.nghia);
							if (input.nghia != L"no")
							{
								system("cls");
								wcout << L"---------------------- Sửa từ -------------------------" << endl;
								wcout << L"Từ: " << input.goc << endl;
								wcout << L"Nghĩa bổ sung: " << input.nghia << endl;
								x = SuaTu2(Dic, input);
							}
						}
						else
						{
							if (check == L"3")
							{
								system("cls");
								wcout << L"---------------------- Xóa từ -------------------------" << endl;
								wcout << L"Từ: " << input.goc << endl;
								wcout << L"Nghĩa: " << input.nghia << endl;

								wcout << L"Bạn có chắc chắn muốn xóa từ này khỏi Từ điển?" << endl;
								wcout << L"Nhập 'yes' để xác nhận hoặc nhập 'no' để hủy." << endl;
								wstring funcinput;
								getline(wcin, funcinput);
								while (funcinput != L"yes" && funcinput != L"no") {
									wcout << L"Bạn vui lòng nhập chính xác 'yes' hoặc 'no'" << endl;
									getline(wcin, funcinput);
								}
								if (funcinput == L"yes")
									x = XoaTu(Dic, input);
							}
						}
					}
					if (x == 0)
					{
						wcout << L"Đã chỉnh sửa thành công.\n" << endl;
						wcout << L"\n------------------------------------------------------------------------------" << endl;
						wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
						wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
					}
					else
					{
						if (x == 1)
						{
							wcout << L"Đã chỉnh sửa thất bại. Vui lòng xem lại.\n" << endl;
							wcout << L"\n------------------------------------------------------------------------------" << endl;
							wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
							wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
						}
						else
						{
							system("cls");
							wcout << L"---------------------- Sửa từ -------------------------" << endl;
							wcout << L"Để dừng và quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
							wcout << L"Đã dừng thao tác." << endl;
							wcout << L"\n------------------------------------------------------------------------------" << endl;
							wcout << L"Nếu muốn tiếp tục thêm từ xin hãy nhập tiếp." << endl;
						}
					}
				}
				else
				{
					system("cls");
					wcout << L"---------------------- Sửa từ -------------------------" << endl;

					wcout << L"Từ ";
					HANDLE hConsoleColor;
					hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsoleColor, 14);
					wcout << L"'" << input.goc << L"' ";
					SetConsoleTextAttribute(hConsoleColor, 7);
					wcout << L"chưa có trong từ điển. Vui lòng thêm từ trước khi muốn chỉnh sửa" << endl;
					wcout << L"(Bạn có thể thêm từ mới bằng cách: chọn Thêm từ mới từ Bảng chọn chức năng" << endl;
					wcout << L"\n------------------------------------------------------------------------------" << endl;
					wcout << L"Để quay lại Bảng chọn chức năng hãy nhập 'N'\n" << endl;
				}
			}
		}
	} while (c == 0);
}
void ClearDic(LINKEDLIST Dic[])
{
	for (int i = 0; i < 26; i++)
	{
		NODE* p = Dic[i].pHead;
		NODE* ptemp;
		while (p != NULL) {
			ptemp = p->pNext;
			delete p;
			p = ptemp;
		}
		Dic[i].pHead = Dic[i].pTail = NULL;
	}
}
void TuDien()
{
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);
	LINKEDLIST Dic[26];
	InitList(Dic);
	int x = 0;
	wstring funcinput;
	int check = 0;
	do {
		x = NhapFile(Dic);
		if (x == 1)//xuat hien loi
			wcout << L"Chương trình sẽ dừng vì gặp lỗi. Vui lòng kiểm tra lại." << endl;
		else
		{
			system("cls");
			wcout << L"-------------- Từ điển Anh - Việt ---------------" << endl;
			wcout << L"Hãy chọn chức năng:" << endl;
			wcout << L"1. Tra Từ" << endl;
			wcout << L"2. Tra từ(theo từng chữ)" << endl;
			wcout << L"3. Chỉnh sửa từ điển" << endl;

			wcout << L"0. Thoát chương trình." << endl;
			if (check == 1)
			{
				wcout << L"Bạn đã nhập sai cú pháp" << endl;
				wcout << L"Bạn vui lòng nhập đúng để có thể chọn chức năng và bắt đầu sử dụng Từ điển." << endl;
			}
			getline(wcin, funcinput);
			ChuanHoa(funcinput);
			if (funcinput == L"1")
			{
				TuDien_TraTu(Dic);
				check = 0;
			}
			else
			{
				if (funcinput == L"2")
				{
					TuDien_TraTu2(Dic);
					check = 0;
				}
				else
				{
					if (funcinput == L"3")
					{
						wstring funcinput2;
						int check2 = 0;
						do {
							system("cls");
							wcout << L"-------------- Từ điển Anh - Việt ---------------" << endl;
							wcout << L"------------------- Chỉnh sửa  ---------------" << endl;
							wcout << L"1. Thêm Từ" << endl;
							wcout << L"2. Sửa từ" << endl;
							wcout << L"0. Quay về Bảng chọn chức năng" << endl;
							if (check2 == 1)
								wcout << L"Bạn đã nhập sai cú pháp. Vui lòng nhập lại." << endl;
							getline(wcin, funcinput2);
							ChuanHoa(funcinput2);
							if (funcinput2 == L"1")
							{
								TuDien_ThemTu(Dic);
								funcinput2 = L"0";
							}
							else
							{
								if (funcinput2 == L"2")
								{
									TuDien_SuaTu(Dic);
									funcinput2 = L"0";
								}
								else
									check2 = 1;
							}
						} while (funcinput2 != L"0");
						check = 0;
					}
					else
					{
						check = 1;
					}
				}
			}
			ClearDic(Dic);
		}
	} while (funcinput != L"0" && x == 0);

}
