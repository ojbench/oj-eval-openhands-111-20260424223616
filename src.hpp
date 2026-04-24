#pragma once //include guard

#undef strtok

namespace sjtu {

char *strtok(char * __restrict str, const char * __restrict delim);


char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *next = nullptr;
    
    // If str is provided, start from str; otherwise continue from next
    if (str != nullptr) {
        next = str;
    }
    
    // If next is nullptr or points to end of string, return nullptr
    if (next == nullptr || *next == '\0') {
        return nullptr;
    }
    
    // Skip leading delimiters
    char *token_start = next;
    while (*token_start != '\0') {
        bool is_delim = false;
        for (const char *d = delim; *d != '\0'; ++d) {
            if (*token_start == *d) {
                is_delim = true;
                break;
            }
        }
        if (!is_delim) {
            break;
        }
        ++token_start;
    }
    
    // If we reached end of string, no more tokens
    if (*token_start == '\0') {
        next = token_start;
        return nullptr;
    }
    
    // Find the end of the token
    char *token_end = token_start;
    while (*token_end != '\0') {
        bool is_delim = false;
        for (const char *d = delim; *d != '\0'; ++d) {
            if (*token_end == *d) {
                is_delim = true;
                break;
            }
        }
        if (is_delim) {
            break;
        }
        ++token_end;
    }
    
    // If we found a delimiter, replace it with '\0' and set next
    if (*token_end != '\0') {
        *token_end = '\0';
        next = token_end + 1;
    } else {
        // End of string reached
        next = token_end;
    }
    
    return token_start;
}

}


