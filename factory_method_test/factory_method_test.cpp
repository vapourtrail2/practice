// factory_method_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <memory>

class  IReader {
public:

    virtual ~IReader() = default;

    virtual void read() = 0;
       
};

class DicomReader : public IReader {
public:
    virtual void read() override {
        std::cout << " dicom已经读取" << std::endl; 
    }
};

class RawReader : public IReader {
public:
    virtual void read() override {
        std::cout << " Raw已经读取" << std::endl;
    }
};

//std::unique_ptr<IReader> ImportImage(std::string & type) {
//    if (type == "dicom") {
//        return std::make_unique<DicomReader>();
//    }
//
//    if (type == "raw") {
//        return std::make_unique<RawReader>();
//    }
//}

class ImportImage {
public:

    virtual ~ImportImage() = default;

    void Import() {
        std::unique_ptr<IReader> reader = createReader();
        reader->read();
    }
     
protected:
    virtual std::unique_ptr<IReader> createReader() = 0;
    
};

class RawImport :public ImportImage {
public:
    std::unique_ptr<IReader> createReader() {
        return std::make_unique<RawReader>();
    }
    
};

class DicomImport :public ImportImage {
public:
    std::unique_ptr<IReader> createReader() {
        return std::make_unique<DicomReader>();
    }
};
         
int main()
{
    /*std::string type = "dicom";
    std::unique_ptr reader = ImportImage(type);
    reader->read();*/
    
    std::unique_ptr<ImportImage> Importer;
    Importer = std::make_unique<DicomImport>();
    Importer->Import();

    return 0;
}


