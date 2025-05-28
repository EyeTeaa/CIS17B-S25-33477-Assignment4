#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {
    }

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

class StorageManager {
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    void addItem(const std::shared_ptr<StoredItem>& item) {
        if (!itemById.count(item->getId()))
        {
            itemById[item->getId()] = item;
            itemByDescription[item->getDescription()] = item;
            std::cout << "Successfully added ID : " << item->getId() << std::endl;
        }
        else
        {
            throw DuplicateItemException("ID already exists : " + item->getId());
        }
        // TODO: Add item to both maps, throw if ID already exists
    }

    std::shared_ptr<StoredItem> findById(const std::string& id) const {
        if (itemById.count(id))
        {
            auto item = itemById.at(id);
            std::cout << "Successfully found item, ID : " + item->getId() << std::endl;
            std::cout << "Desc: " << item->getDescription() 
                << ", at " << item->getLocation() << std::endl; 
            return item;
        }
        else
        {
            throw ItemNotFoundException("Cannot find, does not exist ID : " + id);
        }
        // TODO: Return item if found or throw ItemNotFoundException
        return nullptr;
    }

    void removeItem(const std::string& id) {
        if (itemById.count(id))
        {
            auto item = itemById.at(id);
            itemById.erase(item->getId());
            itemByDescription.erase(item->getDescription());
            std::cout << "Successfully removed ID : " + id; 
        }
        else
        {
            throw ItemNotFoundException("Cannot delete, does not exist ID : " + id);
        }
        // TODO: Remove from both maps, throw if not found
    }

    void listItemsByDescription() const {
        for (const auto& pair : itemByDescription)
        {
            auto item = pair.second;
            std::cout << "Description: " << item->getDescription()
                << ", Location: " << item->getLocation() << std::endl;
        }
        // TODO: Iterate over itemByDescription and print info
    }
};

void testDuplicateAddition();
void testItemNotFound();

int main() {
    auto item1 = std::make_shared<StoredItem>("ITEM001", "LED Light", "Aisle 3, Shelf 1");
    auto item2 = std::make_shared<StoredItem>("ITEM002", "Fan Motor", "Aisle 2, Shelf 5");
    StorageManager sm = StorageManager();

    try
    {
        try
        {
            std::cout << "Demonstrating the functionality of Storage Manager Class" << std::endl;
            std::cout << "Adding item: ITEM001 - LED Light" << std::endl; 
            sm.addItem(item1); 
            std::cout << "Adding item: ITEM002 - Fan Motor" << std::endl; 
            sm.addItem(item2); 
            std::cout << "Attempting to add ITEM001 again..." << std::endl; 
            sm.addItem(item1); 
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error " << e.what() << std::endl;
        }

        try
        {
            std::cout << "Retrieving ITEM002..." << std::endl;
            sm.findById(item2->getId());
            std::cout << "Removing ITEM003..." << std::endl; 
            sm.removeItem("ITEM003");
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error " << e.what() << std::endl;
        }

        try
        {
            sm.listItemsByDescription();
        }
        catch (const std::exception& e)
        {
            
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl; 
    }

    // TODO: Create StorageManager and test functionality
}