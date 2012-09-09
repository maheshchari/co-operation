/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */
#ifndef GDCORE_EVENTSREFACTORER_H
#define GDCORE_EVENTSREFACTORER_H
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
namespace gd { class Layout; }
namespace gd { class Project; }
namespace gd { class ExternalEvents; }
namespace gd { class BaseEvent; }
namespace gd { class Instruction; }
namespace gd {typedef boost::shared_ptr<gd::BaseEvent> BaseEventSPtr;}

namespace gd
{

/**
 * \brief Class used to return result when calling EventsRefactorer::SearchInEvents
 *
  \see EventsRefactorer::SearchInEvents
 */
class GD_CORE_API EventsSearchResult
{
public:
    EventsSearchResult(boost::weak_ptr<gd::BaseEvent> event_, std::vector<boost::shared_ptr<gd::BaseEvent> > * eventsList_, unsigned int positionInList_ );
    EventsSearchResult();
    ~EventsSearchResult() {};

    boost::weak_ptr<gd::BaseEvent> event;
    std::vector<boost::shared_ptr<gd::BaseEvent> > * eventsList;
    unsigned int positionInList;
};

/**
 * \brief Class containing functions to do refactoring tasks on events.
 *
 * Class containing functions to do refactoring tasks on events
 * like changing an object name, deleting an object...
 */
class GD_CORE_API EventsRefactorer
{
public:
    /**
     * Replace all occurences of an object name by another name
     * ( include : objects in parameters and in math/text expressions of all events ).
     */
    static void RenameObjectInEvents(gd::Project & project, gd::Layout & layout, std::vector < gd::BaseEventSPtr > & events, std::string oldName, std::string newName);

    /**
     * Remove all actions or conditions using an object
     */
    static void RemoveObjectInEvents(gd::Project & project, gd::Layout & layout, std::vector < gd::BaseEventSPtr > & events, std::string name);

    /**
     * Search for a string in events
     *
     * \return A vector containing EventsSearchResult objects filled with events containing the string
     */
    static std::vector < EventsSearchResult > SearchInEvents(gd::Project & project, gd::Layout & layout, std::vector < gd::BaseEventSPtr > & events,
                                      std::string search,
                                      bool matchCase,
                                      bool inConditions,
                                      bool inAction);

    /**
     * Replace all occurrences of a string in events
     */
    static void ReplaceStringInEvents(gd::Project & project, gd::Layout & layout, std::vector < gd::BaseEventSPtr > & events,
                                      std::string toReplace,
                                      std::string newString,
                                      bool matchCase,
                                      bool inConditions,
                                      bool inActions);

private:
    /**
     * Replace all occurences of an object name by another name in an action
     * ( include : objects in parameters and in math/text expressions ).
     *
     * \return true if something was modified.
     */
    static bool RenameObjectInActions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & instructions, std::string oldName, std::string newName);

    /**
     * Replace all occurences of an object name by another name in a condition
     * ( include : objects in parameters and in math/text expressions ).
     *
     * \return true if something was modified.
     */
    static bool RenameObjectInConditions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & instructions, std::string oldName, std::string newName);

    /**
     * Remove all conditions of the list using an object
     *
     * \return true if something was modified.
     */
    static bool RemoveObjectInConditions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & conditions, std::string name);

    /**
     * Remove all actions of the list using an object
     *
     * \return true if something was modified.
     */
    static bool RemoveObjectInActions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & conditions, std::string name);

    /**
     * Replace all occurences of a string in conditions
     *
     * \return true if something was modified.
     */
    static bool ReplaceStringInConditions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & conditions, std::string toReplace, std::string newString, bool matchCase);

    /**
     * Replace all occurences of a string in actions
     *
     * \return true if something was modified.
     */
    static bool ReplaceStringInActions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & conditions, std::string toReplace, std::string newString, bool matchCase);

    static bool SearchStringInActions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & actions, std::string search, bool matchCase);
    static bool SearchStringInConditions(gd::Project & project, gd::Layout & layout, std::vector < gd::Instruction > & conditions, std::string search, bool matchCase);

    EventsRefactorer() {};
    virtual ~EventsRefactorer() {};
};

}

#endif // GDCORE_EVENTSREFACTORER_H