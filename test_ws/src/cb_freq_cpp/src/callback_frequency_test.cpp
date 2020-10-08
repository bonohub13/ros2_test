#include <chrono>
#include <memory>
// ROS2 dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class CallbackFreq : public rclcpp::Node
{
    public:
        using String = std_msgs::msg::String;

        explicit CallbackFreq(const rclcpp::NodeOptions &options);
    private:
        String msg;
        rclcpp::Subscription<String>::SharedPtr sub;
        void testCB(const String::SharedPtr msg);
};
CallbackFreq::CallbackFreq(const rclcpp::NodeOptions &options=rclcpp::NodeOptions()) : Node("callbackFrequency", "test", options)
{
    using namespace std::placeholders;

    sub = this->create_subscription<String>(
        "/callbackFreq",
        10,
        std::bind(&CallbackFreq::testCB, this, _1));
}
void CallbackFreq::testCB(const String::SharedPtr msg)
{
    this->msg.data = msg->data;
    RCLCPP_INFO(this->get_logger(), "Callback loop ran");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto callbackFreq = std::make_shared<CallbackFreq>();
    rclcpp::spin(callbackFreq);

    rclcpp::shutdown();
    return 0;
}