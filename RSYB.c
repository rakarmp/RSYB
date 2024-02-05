#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void writeToFile(const char *filePath, const char *value) {
  FILE *file = fopen(filePath, "w");
  if (file != NULL) {
    fprintf(file, "%s", value);
    fclose(file);
  }
}

int isFolderExist(const char *folderPath) {
  return access(folderPath, F_OK) == 0;
}

void setIOScheduler() {
  FILE *schedulerFile = popen("find /sys/block/*/queue/scheduler", "r");
  if (schedulerFile != NULL) {
    char schedulerPath[256];
    while (fgets(schedulerPath, sizeof(schedulerPath), schedulerFile) != NULL) {
      schedulerPath[strcspn(schedulerPath, "\n")] = 0;
      char schedulers[256];
      FILE *file = fopen(schedulerPath, "r");
      if (file != NULL) {
        fgets(schedulers, sizeof(schedulers), file);
        fclose(file);
      }
      if (strstr(schedulers, "bfq") != NULL) {
        writeToFile(schedulerPath, "bfq");
        writeToFile(strcat(schedulerPath, "/iostats"), "0");
        writeToFile(strcat(schedulerPath, "/add_random"), "0");
        writeToFile(strcat(schedulerPath, "/nomerges"), "1");
        writeToFile(strcat(schedulerPath, "/rq_affinity"), "0");
        writeToFile(strcat(schedulerPath, "/rotational"), "0");
        writeToFile(strcat(schedulerPath, "/read_ahead_kb"), "128");
        writeToFile(strcat(schedulerPath, "/nr_requests"), "128");
      } else {
        writeToFile(schedulerPath, "cfq");
      }
    }
    pclose(schedulerFile);
  }
}

int main() {
  const char *folderPath = "/data/adb/modules/RSYB";
  if (isFolderExist(folderPath)) {
    writeToFile("/proc/sys/vm/dirty_background_ratio", "10");
    writeToFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor",
                "interactive");
    writeToFile("/sys/devices/system/cpu/cpufreq/interactive/go_hispeed_load",
                "85");
    writeToFile(
        "/sys/devices/system/cpu/cpufreq/interactive/above_hispeed_delay",
        "20000");
    writeToFile("/sys/devices/system/cpu/cpufreq/interactive/boost", "0");
    writeToFile("/sys/module/msm_performance/parameters/touchboost", "0");
    writeToFile(
        "/sys/devices/system/cpu/cpufreq/interactive/max_freq_hysteresis", "0");
    writeToFile("/sys/devices/system/cpu/cpufreq/interactive/align_windows",
                "1");
    writeToFile("/sys/devices/soc/1c00000.qcom,kgsl-3d0/devfreq/"
                "1c00000.qcom,kgsl-3d0/governor",
                "msm-adreno-tz");
    writeToFile("/sys/class/kgsl/kgsl-3d0/devfreq/governor", "msm-adreno-tz");
    writeToFile("/sys/module/adreno_idler/parameters/adreno_idler_active", "1");
    writeToFile("/sys/module/lazyplug/parameters/nr_possible_cores", "4");
    writeToFile("/dev/cpuset/foreground/cpus", "0-1");
    writeToFile("/dev/cpuset/foreground/boost/cpus", "1");
    writeToFile("/dev/cpuset/top-app/cpus", "0-1");

    setIOScheduler();
  } else {
    system("reboot");
  }

  return 0;
}
