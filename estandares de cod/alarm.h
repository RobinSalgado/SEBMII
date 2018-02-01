

int set_alarm(int seconds, int minutes, int hours, int enabled);

int check_status(void);

//This function should be called in an interruption every 1 second
void refresh_hour(void);
