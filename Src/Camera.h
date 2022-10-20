#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"Imgui/imgui.h"
#include"Imgui/imgui_impl_glfw.h"
#include <Imgui/imgui_impl_opengl3.h>

#include <vector>

enum  Camera_Movement
{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
};

const float YAW			= -90.f;
const float PITCH		=  0.0F;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

class Camera
{
public:

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	//GLFWwindow* window;
	
	Camera(/*GLFWwindow* Window*/ glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		/*window = Window;*/
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
		//m_ViewPortHeight = ImGui::GetContentRegionAvail().x;
		//m_ViewPortWeight = ImGui::GetContentRegionAvail().y;
	};
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseScroll(float yoffset);
	~Camera();
	
private:
	uint32_t m_ViewPortHeight;
	uint32_t m_ViewPortWeight;	
	void updateCameraVectors();
};


