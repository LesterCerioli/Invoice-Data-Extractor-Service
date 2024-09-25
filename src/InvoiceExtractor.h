#pragma once 
#include <string>

struct InvoiceData {
    std::string company_name;
    std::string payment_value;
    std::string payment_date;
};
class InvoiceExtractor {
public: 
    static InvoiceData extractFromPDF(const std::string& pdfFilePath);
};