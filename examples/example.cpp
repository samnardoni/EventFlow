#include <EventFlow/EventFlow.h>

struct ExampleMessage
{
    int value;
};

class ExampleMessageHandler : public EventFlow::MessageHandler<ExampleMessage>
{
  public:
    void handle(const ExampleMessage& msg) override
    {
        std::cout << "Received message with value: " << msg.value << std::endl;
    }
};

int
main()
{
    EventFlow::TopicRegistry registry;

    auto example_topic =
      registry.get_topic<ExampleMessage>("example_topic");

    auto handler = std::make_shared<ExampleMessageHandler>();
    EventFlow::Subscriber<ExampleMessage> subscriber(example_topic, handler);

    EventFlow::Publisher<ExampleMessage> publisher(example_topic);
    publisher.publish(ExampleMessage{42});

    return 0;
}
