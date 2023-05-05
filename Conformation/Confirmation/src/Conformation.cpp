#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	// Resize the ImGui window to match the GLFW window size
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
}

int WinMain()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(380, 370, "Confirmation Analysis", NULL, NULL);
	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Load the calibri font file
	const char* fontPath = "C:\\Windows\\Fonts\\calibri.ttf";
	
	ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath, 15.0f);
	ImGui::GetIO().FontGlobalScale = 1.5f;

	
	// Set the GLFW window size callback
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);


	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// Create a new ImGui window at the top left corner
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin("Price Action Confiramtions Calculator");
		static bool rsi = false;
		ImGui::Checkbox("RSI", &rsi);

		static bool volume = false;
		ImGui::Checkbox("Volume", &volume);

		static bool support = false;
		ImGui::Checkbox("Support & Resistance", &support);

		static bool trend = false;
		ImGui::Checkbox("Trendlines", &trend);

		static bool channel = false;
		ImGui::Checkbox("Channels", &channel);

		static bool dbhs = false;
		ImGui::Checkbox("DB, HS, IHS", &dbhs);

		static bool triangle = false;
		ImGui::Checkbox("Triangles", &triangle);

		static bool flag = false;
		ImGui::Checkbox("Flags", &flag);

		static bool candle = false;
		ImGui::Checkbox("Candles", &candle);

		float total_percentage = 0.0f;

		if (rsi)
			total_percentage += 0.5f;
		if (volume)
			total_percentage += 0.1f;
		if (support)
			total_percentage += 0.25f;
		if (trend)
			total_percentage += 0.15f;
		if (channel)
			total_percentage += 0.15f;
		if (dbhs)
			total_percentage += 0.25f;
		if (triangle)
			total_percentage += 0.25f;
		if (flag)
			total_percentage += 0.15f;
		if (candle)
			total_percentage += 0.05f;

		float percentage = total_percentage * 100.0f;

		ImGui::Text("Total percentage: %0.2f%%", percentage);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}