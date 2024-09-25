#pragma once
#include "InvoiceExtractor.h"

class PaymentScheduler {
public:
    
    static bool schedulePayment(const InvoiceData& data);
};