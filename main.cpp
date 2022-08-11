#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <fstream>

const int SUPPOSED_PARAMETERS_COUNT = 5;
enum class DataTypes {
    INTEGER,
    STRING,
    FLOAT
};
enum class SortMethods {
    ASCENDING,
    DESCENDING
};

std::map<std::string , DataTypes> map_key_to_datatype_parameter = {
        {"i", DataTypes::INTEGER},
        {"s", DataTypes::STRING},
        {"f", DataTypes::FLOAT}
};
std::map<std::string , SortMethods> map_key_to_sort_method_parameter = {
        {"a", SortMethods::ASCENDING},
        {"d", SortMethods::DESCENDING}
};

class LaunchParameters {
public:
    LaunchParameters(const int& parameters_count, char**& raw_parameters) {
        assert(parameters_count == SUPPOSED_PARAMETERS_COUNT);
        this->data_type = map_key_to_datatype_parameter[raw_parameters[1]];
        this->sort_method = map_key_to_sort_method_parameter[raw_parameters[2]];
        this->input_file = raw_parameters[3];
        this->output_file = raw_parameters[4];
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
    DataTypes data_type;
    SortMethods sort_method;
    std::string input_file;
    std::string output_file;
};
class FileHandler {
public:
    FileHandler(std::string file_name) {
        this->file_name = file_name;
    }
    void open_file() {
        this->opened_file.open(this->file_name, std::fstream::out);
        std::cout << opened_file.is_open() << std::endl;
    }
    void read_opened_file() {

    }


private:
    std::string file_name;
    std::fstream opened_file;
    char** lines;
};

int main(int argc, char** argv) {
    LaunchParameters launch_parameters(argc, argv);

    FileHandler input_file(launch_parameters.getInputFile());
    input_file.open_file();

    return 0;
}
