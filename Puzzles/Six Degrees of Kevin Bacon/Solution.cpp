#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct Movie
{
	std::string title;
	std::vector<std::string> actors;
};

static uint32_t ParseInteger()
{
	uint32_t value;
	std::cin >> value;
	std::cin.ignore();
	return value;
}

static std::string ParseLine()
{
	std::string line;
	getline(std::cin, line);
	return line;
}

static void ParseMovies(std::vector<Movie>& movies, uint32_t movieCount)
{
	for (uint32_t i = 0; i < movieCount; i++)
	{
		const std::string movieDetails = ParseLine();
		const uint32_t colonIndex = movieDetails.find_first_of(":");

		Movie movie;
		movie.title = movieDetails.substr(0, colonIndex);

		uint32_t lastIndex = colonIndex + 2;
		const uint32_t endIndex = movieDetails.length();
		while (lastIndex < endIndex)
		{
			const auto nextCommaIndex = movieDetails.find_first_of(",", lastIndex);

			if (nextCommaIndex == std::string::npos)
			{
				movie.actors.push_back(movieDetails.substr(lastIndex, endIndex - lastIndex));
				break;
			}

			movie.actors.push_back(movieDetails.substr(lastIndex, nextCommaIndex - lastIndex));
			lastIndex = nextCommaIndex + 2;
		}
		movies.push_back(movie);
	}
}

static uint32_t ShortestPathLeadingToKevinBacon(const std::vector<Movie>& movies, const std::string& actorName)
{
	std::unordered_map<std::string, std::vector<std::string>> actorsWorkedWith;
	std::unordered_map<std::string, bool> visitedActors;
	std::queue<std::pair<std::string, int>> actorsToVisit;

	// The actor we are looking for is Kevin Bacon
	const std::string targetActor = "Kevin Bacon";

	// Retrieve all actors an actor has worked with
	for (const Movie& movie : movies)
	{
		for (const std::string& actor : movie.actors)
		{
			for (const std::string& coActor : movie.actors)
			{
				if (actor != coActor)
					actorsWorkedWith[actor].push_back(coActor);
			}
		}
	}

	actorsToVisit.push({actorName, false});
	visitedActors[actorName] = true;

	// Doing the BFS algorithm
	while (!actorsToVisit.empty())
	{
		const auto [currentActor, degree] = actorsToVisit.front();
		actorsToVisit.pop();

		if (currentActor == targetActor)
			return degree;

		for (const std::string& coActor : actorsWorkedWith.at(currentActor))
		{
			if (!visitedActors.contains(coActor))
			{
				visitedActors[coActor] = true;
				actorsToVisit.push({coActor, degree + 1});
			}
		}
	}

	return INT32_MAX;
}

int main()
{
	const std::string actorName = ParseLine();
	const uint32_t movieCount = ParseInteger();

	std::vector<Movie> movies;
	ParseMovies(movies, movieCount);

	std::cout << ShortestPathLeadingToKevinBacon(movies, actorName) << std::endl;
}
