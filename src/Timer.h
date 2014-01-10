class Timer
{
	private:
	//clock time when timer started
	int startTicks;
	//stored ticks when paused
	int pausedTicks;
	//status
	bool paused;
	bool started;
	
	public:
	//initialize stuff
	Timer();
	
	//commands
	void start();
	void stop();
	void pause();
	void unpause();

	//get timer's time
	int getTicks();

	//status of the timer
	bool isStarted();
	bool isPaused();
};
