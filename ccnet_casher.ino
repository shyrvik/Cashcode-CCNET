//uint8_t CashCode_poll[] = { 0x02, 0x03, 0x06, 0x33, 0xDA, 0x81 };
uint8_t CashCode_ack[] = { 0x02, 0x03, 0x06, 0x00, 0xC2, 0x82 };
//uint8_t CashCode_reset[] = { 0x02, 0x03, 0x06, 0x30, 0x41, 0xB3 };
uint8_t CashCode_initialized[] = { 0x02, 0x03, 0x06, 0x19, 0x82, 0x0F };

//uint8_t CashCode_request[] = { 0x02, 0x03, 0x06, 0x37, 0xFE, 0xC7 };
//uint8_t CashCode_request_type[] = { 0x02, 0x03, 0x06, 0x41, 0x4F, 0xD1 };

uint8_t CashCode_request_reply[] = { 0x02, 0x03, 0x27, 0x56, 0x55, 0x2D, 0x55, 0x41, 0x31, 0x38, 0x33, 0x37, 0x41, 0x46, 0x20, 0x20, 0x20, 0x20, 0x30, 0x30, 0x4B, 0x35, 0x30, 0x35, 0x30, 0x32, 0x31, 0x38, 0x31, 0x31, 0x41, 0x10, 0x00, 0x00, 0x00, 0xC9, 0xFF, 0xBB, 0x46 };
uint8_t CashCode_request_type_reply[] = { 0x02, 0x03, 0x7D, 0x05, 0x55, 0x4B, 0x52, 0x00, 0x01, 0x55, 0x4B, 0x52, 0x01, 0x02, 0x55, 0x4B, 0x52, 0x01, 0x05, 0x55, 0x4B, 0x52, 0x01, 0x01, 0x55, 0x4B, 0x52, 0x02, 0x02, 0x55, 0x4B, 0x52, 0x02, 0x05, 0x55, 0x4B, 0x52, 0x02, 0x01, 0x55, 0x4B, 0x52, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF9, 0xE7 };
//uint8_t CashCode_enable[] = { 0x02, 0x03, 0x0C, 0x34, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x27, 0xCC };
//uint8_t CashCode_disable[] = { 0x02, 0x03, 0x0C, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x0C };
uint8_t CashCode_bill_type[] = { 0x02, 0x03, 0x06, 0x41, 0x4F, 0xD1 };

uint8_t CashCode_idling[] = { 0x02, 0x03, 0x06, 0x14, 0x67, 0xD4 };             //wait
uint8_t CashCode_scan[] = { 0x02, 0x03, 0x06, 0x15, 0xEE, 0xC5 };               //scan
uint8_t CashCode_50uah[] = { 0x02, 0x03, 0x07, 0x80, 0x03, 0x9E, 0x10 };        //50 uah
uint8_t CashCode_1000uah[] = { 0x02, 0x03, 0x07, 0x80, 0x07, 0x33, 0x47 };        //1000 uah
uint8_t CashCode_depon[] = { 0x02, 0x03, 0x06, 0x17, 0xFC, 0xE6 };              //banknote stacking
uint8_t CashCode_50uah_state[] = { 0x02, 0x03, 0x07, 0x81, 0x03, 0x46, 0x09 };  //50 uah already laid
uint8_t CashCode_1000uah_state[] = { 0x02, 0x03, 0x07, 0x81, 0x07, 0xEB, 0x5E };  //1000 uah already laid
// uint8_t CashCode_stack[] = {0x02, 0x03, 0x06, 0x35, 0xEC, 0xE4};

uint8_t start_byte_02 = 0x02;
uint8_t start_byte_type = 0x03;
uint8_t uart_byte;
int bill_status = 0;
int butt_state;
int send_msg = 0;
int count = 3;
int size_packet;
int ok = 1;

typedef enum {
  IDLE,
  START_BYTE_2,
  SIZE,
  DATA,
  DATA1,
  DATA2,
  PACKET_OK,
} packet_state_t;

typedef enum {
  ACK = 0x00,
  POLL = 0x33,
  INIT = 0x34,
  REQUEST = 0x37,
  REQUEST_TYPE = 0x41,
  DEPONATION = 0x35,
  RESET = 0x30,
} msg_t;

typedef enum {
  IDILING_BILL,
  SCAN,
  DEPONAT,
  DEPON,
  DEPON_STATE,
  IDIL,
} cash_status_t;

typedef enum {
  NUM_50,
  NUM_1000,
} cash_t;

typedef enum {
  NUM_50_STATE,
  NUM_1000_STATE,
} cash_state_t;

uint8_t data_array[6] = {};
packet_state_t state = IDLE;
msg_t msg = ACK;
cash_status_t cash_status = SCAN;
cash_t cash;
cash_state_t cash_state;
 

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, interrupt_1, FALLING);
  attachInterrupt(1, interrupt_10, FALLING);
  Serial.begin(9600, SERIAL_8N1);
}

void erase() {
  for (int i = 0; i <= 5; i++) data_array[i] = 0;
  count = 3;
  ok = 1;
  state = IDLE;
}

void interrupt_1() {
butt_state = 1;
cash = NUM_50;
cash_state = NUM_50_STATE;
}

void interrupt_10() {
butt_state = 2;
cash = NUM_1000;
cash_state = NUM_1000_STATE;
}

void loop() {
  while (Serial.available() && ok == 1) {
    uart_byte = Serial.read();
    switch (state) {
      case IDLE:
        start_byte_02 == uart_byte ? state = START_BYTE_2 : state = IDLE;
        data_array[0] = uart_byte;
      break;
      case START_BYTE_2:
        start_byte_type == uart_byte ? state = SIZE : state = IDLE;
        data_array[1] = uart_byte;
      break;
      case SIZE:
        size_packet = uart_byte - 1;
        data_array[2] = uart_byte;
        state = DATA;
      break;
      case DATA:
        if (count <= size_packet) {
          data_array[count] = uart_byte;
          if (count == size_packet){
            ok = 0;
            packet_ok();
            
          } else {
            state = DATA;
            }
          count++;
        }
         
      break;
    }
  }
}

void packet_ok() {
  switch (data_array[3]) {
    case ACK:
      erase();
    break;
    case POLL:
      /////////////////////////////////waiting for payment/////////////////
      if (bill_status == 1 && butt_state == 0 ) {
        Serial.write(CashCode_idling, sizeof(CashCode_idling));
      }
      //////////////////////////////////payment process////////////////
      else if (bill_status == 1 && butt_state > 0) {
        switch (cash_status) {
          case SCAN:
            Serial.write(CashCode_scan, sizeof(CashCode_scan));
            cash_status = DEPON;
            break;
          case DEPON:
              switch (cash) {
                case NUM_50:
                Serial.write(CashCode_50uah, sizeof(CashCode_50uah));
                break;
                case NUM_1000:
                Serial.write(CashCode_1000uah, sizeof(CashCode_1000uah));
                break;
              } 
            cash_status = DEPONAT;            
          break;
          case DEPONAT:
            Serial.write(CashCode_depon, sizeof(CashCode_depon));
            if (send_msg <= 5) {
              send_msg ++;
            }
            else {
              cash_status = DEPON_STATE;
              send_msg = 0;
            }   
          break;
          case DEPON_STATE:
              switch (cash_state) {
                case NUM_50_STATE:
                Serial.write(CashCode_50uah_state, sizeof(CashCode_50uah_state));
                break;
                case NUM_1000_STATE:
                Serial.write(CashCode_1000uah_state, sizeof(CashCode_1000uah_state));
                break;
              } 
            cash_status = SCAN;
            butt_state = 0;
          break;
        }
      }
      ///////////////////////////////////Waiting for payment///////////////////////////
      else { 
        Serial.write(CashCode_initialized, sizeof(CashCode_initialized));
        butt_state = 0;
      }
    break;
    case INIT:  // initialization of payment waiting mode
      Serial.write(CashCode_ack, sizeof(CashCode_ack));
      data_array[5] == 0xFF ? bill_status = 1 : bill_status = 0;
    break;
    case DEPONATION:
      Serial.write(CashCode_ack, sizeof(CashCode_ack));
    break;
      //////////////////////////////////////////Banknote initialization/////////////////////////////////////////////////////
    case REQUEST:
      Serial.write(CashCode_request_reply, sizeof(CashCode_request_reply));
    break;
    case REQUEST_TYPE:
      Serial.write(CashCode_request_type_reply, sizeof(CashCode_request_type_reply));
      break;
    case RESET:
      Serial.write(CashCode_ack, sizeof(CashCode_ack));
      bill_status = 0;
    break;
  }
    erase();
}


