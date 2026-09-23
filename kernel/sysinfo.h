// estructura que contiene información del sistema
struct sysinfo {
  uint64 free_memory_mb;
  uint64 used_pages;
  uint64 available_pages;
  uint64 total_pages;
  uint64 runnable_processes;
};