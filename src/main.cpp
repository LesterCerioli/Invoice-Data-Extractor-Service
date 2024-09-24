#include "crow_all.h"
#include "InvoiceExtractor.h"
#include "PaymentScheduler.h"

int main() {
    crow::SimpleApp app;

    // Define POST route for invoice processing
    CROW_ROUTE(app, "/process_invoice").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "Invalid JSON format");
        }

        // Extract PDF file path from the request
        std::string pdf_file_path = json_data["pdf_file"].s();

        // Extract invoice data
        InvoiceData invoice_data = InvoiceExtractor::extractFromPDF(pdf_file_path);
        if (invoice_data.company_name.empty() || invoice_data.payment_value.empty() || invoice_data.due_date.empty()) {
            return crow::response(500, "Error extracting invoice data");
        }

        // Schedule payment
        bool success = PaymentScheduler::schedulePayment(invoice_data);
        if (success) {
            return crow::response(200, "Payment scheduled successfully");
        } else {
            return crow::response(500, "Failed to schedule payment");
        }
    });

    // Start server
    app.port(8080).multithreaded().run();
}
