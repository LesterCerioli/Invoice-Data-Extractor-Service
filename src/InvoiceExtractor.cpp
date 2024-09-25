#include "InvoiceExtractor.h"
#include <poppler/glib/poppler-document.h>
#include <iostream>

InvoiceData InvoiceExtractor::exytactFromPDF(const std::string& pdfFilePath) {
    InvoiceData data;

    GError* error = nullptr;
    PopplerDocument* document = poppler_document_new_from_file(("file://" + pdfFilePath).c_str(), nullptr, &error);
    if (!document) {
        std::cerr << "Failed to open PDF: " << error->message << std::endl;
        g_error_free(error);
        return data;
    }

    //Extracting text
    PopplerPage* page = poppler_document_get_page(document, 0);
    if (page) {
        gchar* text = poppler_page_get_text(page);
        std::string full_text(text);
        g_free(text);

        // Data mock        data.company_name = "Extracted Company Name";   // Parse actual company name from full_text
        data.payment_value = "1234.56";                 // Parse the payment value from full_text
        data.due_date = "01/12/2024";                   // Parse the due date from full_text

        g_object_unref(page);
    }
    g_object_unref(document);
    return data;

}