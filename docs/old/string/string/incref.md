
# string_t::incref

Manually increments the reference count of this string.

## Syntax

```cpp
void incref();
```

## Remarks

You must also manually call [string_t::decref](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/string/decref.md) in order to prevent a string leaking into the underlying string pool.

If you frequently refer to a particular string, make sure at least one reference count exists at all times to avoid constantly injecting/discarding the string within the underlying string pool. You can use [string_t::incref](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/strpool/incref.md) and [string_t::decref](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/strpool/decref.md) to manually manipulate reference counts to avoid this problem.

## Related Functions

[string_t::decref](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/string/decref.md)  
