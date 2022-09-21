#pragma once
class GameTimer
{
public:
	GameTimer();

	float	DeltaTime()const;
	float	TotalTime()const;


	void	Reset();
	void	Start();
	void	Tick();
	void	Stop();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 m_CurTime;
	__int64 m_StopTime;
	__int64 m_BaseTime;
	__int64 m_PrevTime;
	__int64 m_PauseTime;

	bool	m_IsStop;
};

