#include "FACE/String_Manager.h"
#include "dds/DCPS/Service_Participant.h"
#include <cstring>

namespace FACE {

namespace {
  static Char s_empty = 0;
  static WChar s_wempty = 0;
}

Char* string_alloc(UnsignedLong len)
{
  if (len == 0) return &s_empty;
  void* const raw = TheServiceParticipant->pool_malloc(len + 1);
  Char* const str = static_cast<Char*>(raw);
  if (str) str[0] = static_cast<Char>(0);
  return str;
}

Char* string_dup(const Char* str)
{
  if (!str) return 0;
  if (!*str) return &s_empty;
  const size_t len = std::strlen(str);
  Char* const cpy = string_alloc(static_cast<UnsignedLong>(len));
  if (cpy) std::strncpy(cpy, str, len + 1);
  return cpy;
}

void string_free(Char* str)
{
  if (str != &s_empty) TheServiceParticipant->pool_free(str);
}

WChar* wstring_alloc(UnsignedLong len)
{
  if (len == 0) return &s_wempty;
  void* const raw = TheServiceParticipant->pool_malloc((len + 1) * sizeof(WChar));
  WChar* const str = static_cast<WChar*>(raw);
  if (str) str[0] = static_cast<WChar>(0);
  return str;
}

WChar* wstring_dup(const WChar* str)
{
  if (!str) return 0;
  if (!*str) return &s_wempty;
  const size_t len = std::wcslen(str);
  WChar* const cpy = wstring_alloc(static_cast<UnsignedLong>(len));
  if (cpy) std::wcsncpy(cpy, str, len + 1);
  return cpy;
}

void wstring_free(WChar* str)
{
  if (str != &s_wempty) TheServiceParticipant->pool_free(str);
}

}
