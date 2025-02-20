#include <iostream>
#include <vector>

class Linker {
public:
    std::string link(const std::vector<std::string>& object_files) {
        std::string final_code = "";
        for (const auto& file : object_files) {
            final_code += file;
        }
        return final_code;
    }
};
