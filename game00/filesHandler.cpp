#include "filesHandler.h"
#include <Windows.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <shobjidl.h> 
#include <filesystem>
#include <fstream>

namespace sf = std::filesystem;

std::string wstring_to_string(const std::wstring& wstr) {
    std::string str(wstr.begin(), wstr.end());
    return str;
}

std::string filesHandler::getFilePath()
{
	OPENFILENAME ofn;
	char file_name[1000] {};
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner =
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 1000;
	ofn.lpstrFilter = "ALL files\0*.*";
	ofn.nFilterIndex = 1;
	GetOpenFileName(&ofn);

	return ofn.lpstrFile;

}

std::string filesHandler::getfolderPath()
{
    IFileDialog* pfd;

    std::wstring folderPath;
    if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
    {
        DWORD dwOptions;
        if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
        {
            pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
        }
        if (SUCCEEDED(pfd->Show(NULL)))
        {
            IShellItem* psi;
            if (SUCCEEDED(pfd->GetResult(&psi)))
            {
                //if (!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &g_path)))
                //{
                //    MessageBox(NULL, "GetIDListName() failed", NULL, NULL);
                //}
                psi->Release();

                PWSTR pszPath;

                psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);

                folderPath = pszPath;
            }
        }
        pfd->Release();
    }

    // Create a wstring_convert object
    //std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    //// Convert wstring to string
    std::string str = wstring_to_string(folderPath);

    return str;
}

void filesHandler::createfolder(std::string path, std::string name)
{
    std::string directory = path + "/" + name;
    sf::create_directory(directory);
}

void filesHandler::createJsonFile(std::string path, std::string name)
{
    std::string directory = path + "/" + name + ".json";
    std::ofstream ofs(directory);
    ofs.close();
}
