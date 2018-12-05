void sckBegin();
boolean sckFindInResponse(const char *toMatch, unsigned int timeOut = 1000);
void sckRecovery();
void sckSkipRemainderOfResponse(unsigned int timeOut);
boolean sckSendCommand(const __FlashStringHelper *command,
                                 boolean isMultipartCommand = false,
                                 const char *expectedResponse = "AOK");

boolean sckSendCommand(const char *command,
                                 boolean isMultipartCommand = false,
                                 const char *expectedResponse = "AOK");


boolean sckEnterCommandMode();
boolean sckSleep();
boolean sckReset();
boolean sckUpdate();
boolean sckExitCommandMode();
boolean sckConnect();
void sckRepair();
boolean sckReady();
char* itoa(int32_t number);
int read_message( const char *msg, int len );
int read_line( char *line );
void send_response( const char *data );
void handle_connection( int val );
