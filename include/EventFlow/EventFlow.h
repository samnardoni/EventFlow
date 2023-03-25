#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace EventFlow {
template<typename MessageType>
class MessageHandler
{
  public:
    virtual ~MessageHandler() = default;
    virtual void handle(const MessageType& msg) = 0;
};

template<typename MessageType>
class Topic
{
  public:
    void subscribe(const std::shared_ptr<MessageHandler<MessageType>>& handler)
    {
        handlers.push_back(handler);
    }

    void unsubscribe(
      const std::shared_ptr<MessageHandler<MessageType>>& handler)
    {
        handlers.erase(std::remove(handlers.begin(), handlers.end(), handler),
                       handlers.end());
    }

    void publish(const MessageType& msg)
    {
        for (const auto& handler : handlers) {
            handler->handle(msg);
        }
    }

  private:
    std::vector<std::shared_ptr<MessageHandler<MessageType>>> handlers;
};

class TopicRegistry
{
  public:
    template<typename MessageType>
    std::shared_ptr<Topic<MessageType>> get_topic(const std::string& topic_name)
    {
        const auto it = topics.find(topic_name);
        if (it != topics.end()) {
            // TODO: type safety
            return std::static_pointer_cast<Topic<MessageType>>(it->second);
        } else {
            auto new_topic = std::make_shared<Topic<MessageType>>();
            topics[topic_name] = new_topic;
            return new_topic;
        }
    }

  private:
    std::unordered_map<std::string, std::shared_ptr<void>> topics;
};

template<typename MessageType>
class Publisher
{
  public:
    Publisher(const std::shared_ptr<Topic<MessageType>>& topic)
      : topic(topic)
    {
    }

    void publish(const MessageType& msg) { topic->publish(msg); }

  private:
    std::shared_ptr<Topic<MessageType>> topic;
};

template<typename MessageType>
class Subscriber
{
  public:
    Subscriber(const std::shared_ptr<Topic<MessageType>>& topic,
               const std::shared_ptr<MessageHandler<MessageType>>& handler)
      : topic(topic)
      , handler(handler)
    {
        topic->subscribe(handler);
    }

    ~Subscriber() { topic->unsubscribe(handler); }

  private:
    std::shared_ptr<Topic<MessageType>> topic;
    std::shared_ptr<MessageHandler<MessageType>> handler;
};
}
