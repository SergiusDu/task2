#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include "algorithm"





class LaunchParameters {
public:
    enum class DataTypes :std::uint8_t {
        INTEGER,
        STRING,
        FLOAT
    };
    enum class SortMethods :std::uint8_t{
        ASCENDING,
        DESCENDING
    };
    LaunchParameters(const int& parameters_count, char**& raw_parameters) {
        assert(parameters_count == SUPPOSED_PARAMETERS_COUNT);
        ParseParameters(parameters_count, raw_parameters);
    }

    [[nodiscard]] DataTypes getDataType() const {
        return data_type;
    }

    [[nodiscard]] SortMethods getSortMethod() const {
        return sort_method;
    }

    [[nodiscard]] const std::string &getInputFile() const {
        return input_file;
    }

    [[nodiscard]] const std::string &getOutputFile() const {
        return output_file;
    }
private:
    const int SUPPOSED_PARAMETERS_COUNT = 5;
    const std::unordered_map<std::string , DataTypes> map_key_to_datatype_parameter = {
            {"i", DataTypes::INTEGER},
            {"s", DataTypes::STRING},
            {"f", DataTypes::FLOAT}
    };
    const std::unordered_map<std::string , SortMethods> map_key_to_sort_method_parameter = {
            {"a", SortMethods::ASCENDING},
            {"d", SortMethods::DESCENDING}
    };

    DataTypes data_type {};
    SortMethods sort_method {};
    std::string input_file {};
    std::string output_file {};
    void ParseParameters(const int& parameters_count, char**& raw_parameters) {
        for(size_t index = 1; index < parameters_count; index++) {
            auto parameter = raw_parameters[index];
            if(map_key_to_datatype_parameter.contains(parameter)){
                data_type = map_key_to_datatype_parameter.at(parameter);
                continue;
            }
            if(map_key_to_sort_method_parameter.contains(parameter)) {
                sort_method = map_key_to_sort_method_parameter.at(parameter);
                continue;
            }
            if(input_file.empty()) {
                input_file = parameter;
                continue;
            }
            if(output_file.empty()) {
                output_file = parameter;
                continue;
            }
        }

    }


};
class FileContentSorter {
public:
    explicit FileContentSorter(LaunchParameters& launch_parameters) { /* TODO What does 'explicit' mean?*/
        this->extract_file_content_to_vector(launch_parameters.getInputFile());
        this->SortFileContent(launch_parameters.getDataType(),
                              launch_parameters.getSortMethod());
        this->save_sorted_content_in_output_file(launch_parameters.getOutputFile());
    }
    void extract_file_content_to_vector(auto& input_file_name) {
        this->opened_file.open(input_file_name, std::fstream::in);
        if (this->opened_file.is_open()) {
            std::cout << "OPENED" << std::endl;
            std::string line;
            while (getline(this->opened_file, line)) {
                this->file_content.push_back(line);
            }
            this->opened_file.close();
        }
        else {
            std::cout << "Can't open file" << std::endl;
        }
    }
    void SortFileContent(const LaunchParameters::DataTypes& data_type,
                         const LaunchParameters::SortMethods& sort_method) {
        switch (sort_method) {
            case (LaunchParameters::SortMethods::ASCENDING):
                std::sort(this->file_content.begin(), this->file_content.end(),
                          [](const auto& lhs,const auto& rhs) {
                              return lhs < rhs;
                          });
                break;
            case LaunchParameters::SortMethods::DESCENDING:
                std::sort(this->file_content.begin(), this->file_content.end(),
                          [](const auto& lhs, const auto& rhs) {
                              return lhs > rhs;
                          });
                break;
            default:
                assert("Unknown search method");
                break;
        }

    }
    void save_sorted_content_in_output_file(const std::string& output_file_name) {
        opened_file.open(output_file_name, std::fstream::out);
        if(opened_file.is_open()) {
            for(const auto& line : this->file_content) {
                opened_file << line << '\n';
            }
            opened_file.close();
        } else {
            std::cout << "File isn't opened" << std::endl;
        }
    }

private:
    std::fstream opened_file;
    std::vector<std::string> file_content;
};

int main(int argc, char** argv) {
    LaunchParameters launch_parameters(argc, argv);
    FileContentSorter file_sorter(launch_parameters);
    return 0;
}
