--------------

**void array_print_byte**(*byt*e **arr[]**, *uint16_t* **len**, *char* **delim**)

**void array_print_int**(*int* **arr[]**, *uint16_t* **len**, *char* **delim**)

**void array_print_float**(*float* **arr[]**, *uint16_t* **len**, *char* **delim**, *byte* **places**)

Prints **arr[]** (of length **len**) over Serial, delimited by **delim**. Must use the function specific to the data type of the array. Float arrays must specify how many decimal **places** are printed.

--------------

void array_shift_byte(byte arr[], uint16_t len, float newVal);
void array_shift_int(int arr[], uint16_t len, float newVal);
void array_shift_float(float arr[], uint16_t len, float newVal);

	Shift values in arr[] (of length len) one place to the left, and appends newVal to the end to allow an array to act as a buffer or log.
