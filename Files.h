#include <File.h>
#include <FilePanel.h>

#ifndef FILES_H
#define FILES_H

namespace ToDo {
    class Files {
        public:
            std::vector<Item> ReadFile(const entry_ref &ref);
			void WriteFile(const char* path);
        private:
            std::vector<std::string> SplitString(std::string delimiter, std::string haystack);
            bool CheckFile(*BFile file)
    }
}

#endif
