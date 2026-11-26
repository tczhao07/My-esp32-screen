
#include <SPI.h>
#include <SD.h>

// ==================== Pin Configuration ====================

constexpr uint8_t SD_SCK  = 13;
constexpr uint8_t SD_MISO = 25;
constexpr uint8_t SD_MOSI = 14;
constexpr uint8_t SD_CS   = 5;

// SPI clock: 4 MHz
constexpr uint32_t SPI_FREQ = 4000000;

// Test file
constexpr char TEST_FILE[] = "/sd_test.txt";

// ==================== SPI Initialization ====================

void InitSPI()
{
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
}

// ==================== Card Information ====================

void PrintCardInfo()
{
    Serial.println("\n========== SD CARD INFO ==========");

    uint8_t type = SD.cardType();

    if (type == CARD_NONE)
    {
        Serial.println("No SD card detected.");
        return;
    }

    Serial.print("Card Type: ");

    switch (type)
    {
        case CARD_MMC:
            Serial.println("MMC");
            break;

        case CARD_SD:
            Serial.println("SDSC");
            break;

        case CARD_SDHC:
            Serial.println("SDHC / SDXC");
            break;

        default:
            Serial.println("Unknown");
            break;
    }

    Serial.printf(
        "Card Size: %llu MB\n",
        SD.cardSize() / (1024ULL * 1024ULL)
    );

    Serial.printf(
        "Used Space: %llu MB\n",
        SD.usedBytes() / (1024ULL * 1024ULL)
    );

    Serial.printf(
        "Total Space: %llu MB\n",
        SD.totalBytes() / (1024ULL * 1024ULL)
    );
}

// ==================== Write Test ====================

bool WriteTest()
{
    Serial.println("\n========== WRITE TEST ==========");

    // Remove previous test file
    if (SD.exists(TEST_FILE))
    {
        SD.remove(TEST_FILE);
    }

    File file = SD.open(TEST_FILE, FILE_WRITE);

    if (!file)
    {
        Serial.println("Failed to open file for writing.");
        return false;
    }

    const char *data =
        "ESP32 MicroSD Test\n"
        "SPI Communication: OK\n"
        "Write Test: SUCCESS\n";

    size_t written = file.print(data);

    file.flush();
    file.close();

    if (written != strlen(data))
    {
        Serial.println("Write incomplete.");
        return false;
    }

    Serial.printf("Written: %u bytes\n",
                  static_cast<unsigned>(written));

    Serial.println("Write test passed.");

    return true;
}

// ==================== Read Test ====================

bool ReadTest()
{
    Serial.println("\n========== READ TEST ==========");

    File file = SD.open(TEST_FILE, FILE_READ);

    if (!file)
    {
        Serial.println("Failed to open file for reading.");
        return false;
    }

    String content;

    while (file.available())
    {
        content += static_cast<char>(file.read());
    }

    file.close();

    Serial.println("Read Content:");
    Serial.println(content);

    const char *expected =
        "ESP32 MicroSD Test\n"
        "SPI Communication: OK\n"
        "Write Test: SUCCESS\n";

    if (content != expected)
    {
        Serial.println("Data verification FAILED.");
        return false;
    }

    Serial.println("Data verification PASSED.");

    return true;
}

// ==================== Directory Test ====================

void ListFiles()
{
    Serial.println("\n========== ROOT DIRECTORY ==========");

    File root = SD.open("/");

    if (!root || !root.isDirectory())
    {
        Serial.println("Failed to open root directory.");
        return;
    }

    File entry = root.openNextFile();

    while (entry)
    {
        Serial.print(entry.name());

        if (entry.isDirectory())
        {
            Serial.println(" [DIR]");
        }
        else
        {
            Serial.printf(" [%u bytes]\n",
                          static_cast<unsigned>(entry.size()));
        }

        entry.close();
        entry = root.openNextFile();
    }

    root.close();
}

// ==================== Arduino Setup ====================

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("\n================================");
    Serial.println("      ESP32 MICROSD TEST");
    Serial.println("================================");

    InitSPI();

    Serial.println("\nInitializing SD Card...");

    if (!SD.begin(SD_CS, SPI, SPI_FREQ))
    {
        Serial.println("SD initialization FAILED!");
        Serial.println("Check wiring, power and SD card.");
        return;
    }

    Serial.println("SD initialization SUCCESS!");

    PrintCardInfo();

    bool writeOK = WriteTest();
    bool readOK = ReadTest();

    ListFiles();

    Serial.println("\n========== FINAL RESULT ==========");

    Serial.printf("Write Test: %s\n",
                  writeOK ? "PASS" : "FAIL");

    Serial.printf("Read Test: %s\n",
                  readOK ? "PASS" : "FAIL");

    Serial.printf("Overall: %s\n",
                  (writeOK && readOK) ? "SUCCESS" : "FAILED");
}

void loop()
{
    delay(1000);
}

