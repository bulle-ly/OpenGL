#include "GameTimer.h"
#include<Windows.h>

GameTimer::GameTimer()
	:mSecondsPerCount(0.0), mDeltaTime(-1.0), m_BaseTime(0),
	m_PauseTime(0), m_PrevTime(0), m_CurTime(0), m_IsStop(false), m_StopTime(0)
{
	__int64	m_CountPerSecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_CountPerSecond);
	mSecondsPerCount = mSecondsPerCount = 1.0 / (double)m_CountPerSecond;
	//QueryPerformanceCounter((LARGE_INTEGER*)&mSecondsPerCount); ��ȡʱ���
}

float GameTimer::TotalTime()const {


	if (m_IsStop) {
		//��������ͣ״̬ ��Ϸ��ʱ���������ʱ���ȥ��ͣ��ʱ��ͻ���ʱ��
		//  (m_CurTime - m_PauseTime) - m_BaseTime 
//
//                     |<--paused time-->|
// ----*---------------*-----------------*------------*------> time
//  m_BaseTime       m_StopTime        startTime     m_CurTime

		return (float)(((m_StopTime - m_PauseTime) - m_BaseTime) * mSecondsPerCount);

	}
	else {
		return(float)(((m_CurTime - m_PauseTime) - m_BaseTime) * mSecondsPerCount);
	}
}

float GameTimer::DeltaTime()const {
	return (float)mDeltaTime;
}
void GameTimer::Reset() {
	__int64	currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;
	m_IsStop = false;

}

void GameTimer::Start() {
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_IsStop)
	{
		m_PauseTime += (startTime - m_StopTime);

		m_PrevTime = startTime;
		m_StopTime = 0;
		m_IsStop = false;

	}
}

void GameTimer::Stop()
{
	if (!m_IsStop)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_StopTime = currTime;
		m_IsStop = true;
	}
}

void GameTimer::Tick()
{
	if (m_IsStop)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurTime = currTime;

	mDeltaTime = (m_CurTime - m_PrevTime) * mSecondsPerCount;

	m_PrevTime = m_CurTime;

	if (mDeltaTime < 0.0)
	{
		mDeltaTime;
	}
}
