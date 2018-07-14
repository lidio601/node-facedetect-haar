//
// Created by Fabio Cigliano on 02/07/18.
//

#include "types.h"

uv_async_t async;
TMessage *bag;

std::string stringValue(Local<Value> value) {
    if (!value->IsString()) {
        return "";
    }

    // Alloc #1
    char * buffer = (char*) malloc(sizeof(char) * value->ToString()->Utf8Length());
    value->ToString()->WriteUtf8(buffer, value->ToString()->Utf8Length());
    std::string ret(buffer);
    free(buffer);

    return ret;
}
