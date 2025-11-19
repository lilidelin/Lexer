#include<windows.h>
#include<shobjidl.h>
#include "parser/parser.h"
#pragma comment(lib, "ole32.lib")
std::string openFileDialog() {
    HRESULT hr = CoInitializeEx(NULL,COINIT_APARTMENTTHREADED|COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) return "";
    IFileDialog* pFileDialog;
    //创建文件选择对话狂实例
    hr = CoCreateInstance(CLSID_FileOpenDialog,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&pFileDialog));
    if (FAILED(hr)) {
        CoUninitialize();
        return "";
    }
    //设置筛选器
    COMDLG_FILTERSPEC filters[]={
        {L"所有文件",L"*.*"},
        {L"文本文件",L"*.txt"}
    };
    pFileDialog->SetFileTypes(_countof(filters),filters);
    //显示对话狂
    hr = pFileDialog->Show(NULL);
    if (SUCCEEDED(hr)) {
        IShellItem* pItem = NULL;
        hr = pFileDialog->GetResult(&pItem);
        if (SUCCEEDED(hr)) {
            PWSTR pszFilePath;
            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
            if (SUCCEEDED(hr)) {
                std::wstring wstr(pszFilePath);
                std::string path(wstr.begin(), wstr.end());
                CoTaskMemFree(pszFilePath);//释放内存
                pItem->Release();
                pFileDialog->Release();
                CoUninitialize();
                return path;
            }
            pItem->Release();
        }
    }
    pFileDialog->Release();
    CoUninitialize();
    return "";
}
int main() {
    system("mkdir result");
    std::string path = openFileDialog();
    Lexer lexer(path);
    Token current_token;
    // do {
    //     current_token = lexer.get_next_token_1_1();
    //     std::cout<<current_token.value<<" "<<current_token.type<<std::endl;
    // }while (current_token.type != 25);
    Parser parser(lexer);
    parser.Program();
    std::string message =
            "The lexical and syntactic analysis has been completed, and the corresponding analysis results have been generated and saved in the result folder under the current directory.";
    MessageBoxA(NULL, message.c_str(), "Result", MB_OK);
    return 0;
}