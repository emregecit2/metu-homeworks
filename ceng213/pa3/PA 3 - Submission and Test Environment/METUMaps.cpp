#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    map = Graph(mapFilePath);
    this->potentialPathCount = potentialPathCount;
    cachedPaths = KeyedHashTable(map.TotalVertexCount()*potentialPathCount);
    inJourney = false;
}

void METUMaps::SetDestination(const std::string& name)
{
    if(inJourney){
        PrintUnableToChangeDestination();
    }
    else{
        destination = name;
    }
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    if(inJourney){
        PrintUnableToChangeStartingLoc();
    }
    else{
        startingLoc = name;
    }
}

void METUMaps::StartJourney()
{
    if(inJourney){
        PrintAlreadyInJourney();
    }
    else{
        PrintCalculatingRoutes(startingLoc, destination);
        std::vector<std::vector<int> > paths;
        try{
            map.MultipleShortPaths(paths, startingLoc, destination, potentialPathCount);
        }
        catch(VertexNotFoundException){
            PrintLocationNotFound();
            return;
        }
        currentRoute = paths.front();
        for(int i=0; i<paths.size(); i++){
            std::vector<int> &path = paths[i];
            int size = path.size();
            for(int j=1; j<size; j++){
                cachedPaths.Insert(GenerateKey(map.VertexName(path.front()), map.VertexName(path.back())), path);
                path.erase(path.begin());
            }
        }
        inJourney = true;
        currentLoc = startingLoc;
    }
}

void METUMaps::EndJourney()
{
    if(inJourney){
        cachedPaths.ClearTable();
        destination = startingLoc = currentLoc = "";
        inJourney = false;
    }
    else{
        PrintJourneyIsAlreadFinished();
    }
}

void METUMaps::UpdateLocation(const std::string& name)
{
    if(inJourney){
        currentLoc = name;
        if(currentLoc == destination){
            PrintJourneyCompleted();
        }
        else{
            std::vector<int> valueOut;
            if(cachedPaths.Find(valueOut, GenerateKey(name, destination))){
                PrintCachedLocationFound(name, destination);
                currentRoute = valueOut;
            }
            else{
                PrintCalculatingRoutes(name, destination);
                std::vector<std::vector<int> > paths;
                try{
                    map.MultipleShortPaths(paths, name, destination, potentialPathCount);
                }
                catch(VertexNotFoundException){
                    PrintLocationNotFound();
                    return;
                }
                currentRoute = paths.front();
                for(int i=0; i<paths.size(); i++){
                    std::vector<int> &path = paths[i];
                    int size = path.size();
                    for(int j=1; j<size; j++){
                        cachedPaths.Insert(GenerateKey(map.VertexName(path.front()), map.VertexName(path.back())), path);
                        path.erase(path.begin());
                    }
                }
            }
        }
    }
    else{
        PrintNotInJourney();
    }
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}
