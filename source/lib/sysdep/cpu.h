#ifndef SYSDEP_CPU_H
#define SYSDEP_CPU_H

#ifdef __cplusplus
extern "C" {
#endif


const size_t CPU_TYPE_LEN = 49;	// processor brand string is <= 48 chars
extern char cpu_type[CPU_TYPE_LEN];

extern double cpu_freq;

// -1 if detect not yet called, or cannot be determined
extern int cpus;
extern int cpu_speedstep;
extern int cpu_smp;
	// are there actually multiple physical processors,
	// not only logical hyperthreaded CPUs? relevant for wtime.


// not possible with POSIX calls.
// called from ia32.cpp check_smp
extern int on_each_cpu(void(*cb)());

extern void get_cpu_info(void);


// atomic "compare and swap". compare the machine word at <location> against
// <expected>; if not equal, return false; otherwise, overwrite it with
// <new_value> and return true.
extern bool CAS_(uintptr_t* location, uintptr_t expected, uintptr_t new_value);

// this is often used for pointers, so the macro coerces parameters to
// uinptr_t. invalid usage unfortunately also goes through without warnings.
// to catch cases where the caller has passed <expected> as <location> or
// similar mishaps, the implementation verifies <location> is a valid pointer.
#define CAS(l,o,n) CAS_((uintptr_t*)l, (uintptr_t)o, (uintptr_t)n)

extern void atomic_add(intptr_t* location, intptr_t increment);

// enforce strong memory ordering.
extern void mfence();

extern void serialize();

// Win32 CONTEXT field abstraction
// (there's no harm also defining this for other platforms)
#if CPU_AMD64
# define PC_ Rip
# define FP_ Rbp
# define SP_ Rsp
#elif CPU_IA32
# define PC_ Eip
# define FP_ Ebp
# define SP_ Esp
#endif

#ifdef __cplusplus
}
#endif

#endif
