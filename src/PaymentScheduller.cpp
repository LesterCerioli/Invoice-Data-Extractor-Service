#include "PaymentScheduler.h"
#include <iostream>

bool PaymentScheduler::schedulePayment(const InvoiceData& data) {
    
    std::cout << "Scheduling payment for company: " << data.company_name << std::endl;
    std::cout << "Payment value: $" << data.payment_value << std::endl;
    std::cout << "Due date: " << data.due_date << std::endl;

    
    return true;
}
