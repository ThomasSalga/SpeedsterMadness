#include "SM_Controller.h"
#include "ObstacleCar.h"
#include "Game.h"


SM_Controller::SM_Controller()
{
}

SM_Controller::~SM_Controller()
{
}

void SM_Controller::Start()
{
	m_position.x = (m_game->GetWindowSize().x / 3) - (m_dimensions.x / 2);
	m_position.y = (m_game->GetWindowSize().y * 2 / 3) - (m_dimensions.y / 2);

	ReadFromFile();
	m_score = 0;
}

void SM_Controller::Update(float deltaTime, Input input)
{
	//update score
	m_time += deltaTime;

	if (m_time > 1)
	{
		m_score += 10;
		SetHighScore(m_score);
		m_scoreText->SetText(std::to_string(m_score));
		m_time = 0;
	}
	//update Inputs
	if (input.keyboardState[SDL_SCANCODE_RIGHT] || input.keyboardState[SDL_SCANCODE_D])
	{
		if (m_position.x < m_game->GetWindowSize().x /3 - m_dimensions.x + GetMovementArea().x / 2)
			m_position.x += 200 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_LEFT] || input.keyboardState[SDL_SCANCODE_A])
	{
		if (m_position.x > m_game->GetWindowSize().x / 3 - GetMovementArea().x /2)
			m_position.x -= 200 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_UP]|| input.keyboardState[SDL_SCANCODE_W])
	{
		if (m_position.y > 0 )
		m_position.y -= 100 * deltaTime;
	}
	if (input.keyboardState[SDL_SCANCODE_DOWN] || input.keyboardState[SDL_SCANCODE_S])
	{
		if (m_position.y < GetMovementArea().y - m_dimensions.y)
		m_position.y += 200 * deltaTime;
	}

	if (input.mouseState.lPressed)
	{
		if (CollisionPoint(input.mouseState.x, input.mouseState.y))
		{
		}
	}

	if (input.keyboardState[SDL_SCANCODE_ESCAPE])
	{
		m_game->Quit();
	}
}

void SM_Controller::OnCollision(GameObject * collider)
{
	if (collider->m_name.compare(0, 3, "car") == 0)
	{
		std::cout << m_name << " collided with " << collider->m_name << " GAME OVER" << std::endl;
		WriteOnFile(m_highScore);
		//clear scene from obstacles for replay
		std::string name;
		m_game->PlaySound("Impact", 0);
		for (int i = 0; i <= 99; i++)
		{
			name = "car";
			name += std::to_string(i);
			m_game->RemoveObject(name,1);
		}
		m_scoreText->SetText(std::to_string(0));
		m_game->StopSound("Sugar");
		m_game->PlaySound("GameOver", 1);
		m_game->SetActiveScene(2);
	}
}

void SM_Controller::ReadFromFile() 
{
	std::string line;
	std::ifstream myfile("Assets/example.txt");
	if (myfile.is_open())
	{
		if (getline(myfile, line));
		{
			m_highScore = std::stoi(line);
			m_highscoreText->SetText(std::to_string(m_highScore));
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file, creating a new one";
		std::ofstream myfile("Assets/example.txt");
		myfile << "0";
		myfile.close();
	}
}

void SM_Controller::WriteOnFile(int score)
{
	std::string line;
	line = std::to_string(score);
	std::ofstream myfile("Assets/example.txt");

	if (myfile.is_open())
	{
		myfile << line;
		myfile.close();
	}
}

void SM_Controller::SetHighScore(int score)
{
	if (score > m_highScore)
	{
		m_highScore = score;
		m_highscoreText->SetText(std::to_string(m_highScore));
	}
}

int SM_Controller::GetScore()
{
	return m_score;
}

void SM_Controller::AssignTextScore(Text * text)
{
	m_scoreText = text;
}

void SM_Controller::AssignTextHighScore(Text * text)
{
	m_highscoreText = text;
}
