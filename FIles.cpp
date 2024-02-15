#include "Files.h"

namespace ToDo {
    	void MainWindow::WriteFile(const char* path) {
		BFile file(path, B_WRITE_ONLY);

		if (!CheckFile(*file)) {
			std::cout << "bad path\n";	
            return NULL;
		}	

		for (int i = 0; i < Items.size(); i++) {
			std::stringstream ss;
			ss << Items[i].name << "|" <<  Items[i].desc << "|" << Items[i].isChecked << "\n";
			std::string data = ss.str();
			file.Write(data.c_str(), data.size());
		}
	}

	std::vector<Item> MainWindow::ReadFile(const entry_ref &ref) {
		BFile file(&ref, B_READ_ONLY);

		if (!CheckFile(*file)) {
			std::cout << "bad path\n";	
            return NULL;
		}

		off_t fileSize = 0;
		file.GetSize(&fileSize);
		BString fileData;
		char *buffer = fileData.LockBuffer(fileSize + 10);
		file.Read(buffer, fileSize);
		fileData.UnlockBuffer();

        std::vector<Item> Items = {};
		auto lines = SplitString(std::string("\n"), std::string(buffer));
		for (int i = 0; i < lines.size(); i++) {	
			auto res = SplitString(std::string("|"), lines[i]);
			Items.push_back({res[0], res[1], std::stoi(res[2])});
		}
        return Items;
	}

    bool CheckFile(*BFile file) {
        return file.InitCheck() == B_OK;
    }

    std::vector<std::string> MainWindow::SplitString(std::string delimiter, std::string haystack) {
		std::vector<std::string> res = {};	
		size_t next = 0;
		size_t prev = 0;
		while ((next = haystack.find(delimiter, prev)) != std::string::npos) {
			res.push_back(haystack.substr(prev, next-prev));
			prev = next + 1;
		}	
		res.push_back(haystack.substr(prev));
		return res;
	}
}