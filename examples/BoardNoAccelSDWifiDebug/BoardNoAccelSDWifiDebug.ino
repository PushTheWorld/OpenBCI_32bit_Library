#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.beginDebug();
  // don't use accel
  board.useAccel(false);
}

void loop() {
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();
      // Send channel data
      board.sendChannelData();
    }
  }

  // Check the serial port for new data
  if (board.hasDataSerial0()) {
    // Read one char and process it
    board.processChar(board.getCharSerial0());
  }
  if (board.hasDataSerial1()) {
    // Read one char and process it
    board.processChar(board.getCharSerial1());
  }

  if (board.isProcessingMultibyteMsg()) {
    board.tryMultiAbort();
  }
}
