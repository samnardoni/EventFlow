# EventFlow

EventFlow is a lightweight, header-only, in-process publish-subscribe (pub-sub) library for C++17. It allows you to create, publish, and subscribe to topics, enabling efficient communication between different components within your application.

## Features

- Header-only library: no binaries to build or link.
- Simple and clean API for creating publishers and subscribers.
- Type-safe topics: each topic is associated with a specific message type.

## Getting Started

### Prerequisites

- A C++17 compatible compiler.
- CMake 3.14 or later.

### Usage

Include the appropriate headers in your project:

```cpp
#include "EventFlow/EventFlow.h"
```

Define your message type:

```cpp
struct MyMessage
{
    int id;
    std::string text;
};
```

Create a message handler:

```cpp
class ExampleMessageHandler : public EventFlow::MessageHandler<MyMessage>
{
  public:
    void handle(const MyMessage& msg) override
    {
        std::cout << "Received message with id: " << msg.id << " text: " << msg.text << std::endl;
    }
};
```

Create a topic and instantiate a publisher and a subscriber:

```cpp
EventFlow::TopicRegistry registry;
auto topic = registry.get_topic<MyMessage>("example_topic");

EventFlow::Publisher<MyMessage> publisher(topic);

auto handler = std::make_shared<ExampleMessageHandler>();
EventFlow::Subscriber<MyMessage> subscriber(topic, handler);
```

Publish a message:

```cpp
MyMessage msg{42, "Hello, EventFlow!"};
publisher.publish(msg);
```

The subscriber's message handler will be called when a message is published to the topic.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
