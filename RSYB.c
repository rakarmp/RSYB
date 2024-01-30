#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void writeToFile(const char *filePath, const char *value)
{
    FILE *file = fopen(filePath, "w");
    if (file != NULL)
    {
        fprintf(file, "%s", value);
        fclose(file);
    }
}

int isFolderExist(const char *folderPath)
{
    return access(folderPath, F_OK) == 0;
}

int main()
{
    const char *folderPath = "/data/adb/modules/RSYB";
    if (isFolderExist(folderPath))
    {
        writeToFile("/proc/sys/vm/dirty_background_ratio", "20");
        writeToFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor", "interactive");
        writeToFile("/sys/devices/system/cpu/cpufreq/performance/go_hispeed_load", "50");
        writeToFile("/sys/devices/system/cpu/cpufreq/performance/above_hispeed_delay", "0");
        writeToFile("/sys/devices/system/cpu/cpufreq/performance/boost", "0");
        writeToFile("/sys/module/msm_performance/parameters/touchboost", "0");
        writeToFile("/sys/devices/system/cpu/cpufreq/performance/max_freq_hysteresis", "1");
        writeToFile("/sys/devices/system/cpu/cpufreq/performance/align_windows", "1");
        writeToFile("/sys/devices/soc/1c00000.qcom,kgsl-3d0/devfreq/1c00000.qcom,kgsl-3d0/governor", "msm-adreno-tz");
        writeToFile("/sys/class/kgsl/kgsl-3d0/devfreq/governor", "msm-adreno-tz");
        writeToFile("/sys/module/adreno_idler/parameters/adreno_idler_active", "1");
        writeToFile("/sys/module/lazyplug/parameters/nr_possible_cores", "8");
        writeToFile("/dev/cpuset/foreground/cpus", "0-3,4-7");
        writeToFile("/dev/cpuset/foreground/boost/cpus", "3-7");
        writeToFile("/dev/cpuset/top-app/cpus", "0-7");
    }
    else
    {
        system("reboot");
    }

    return 0;
}
