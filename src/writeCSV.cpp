//
// Created by agruet on 2/10/23.
//

#include <ros/ros.h>
#include <fstream>
#include <sensor_msgs/PointCloud2.h>

/**
 * @brief Class dedicated to the verification of LiDARs timestamps.
 */
class WriteCSV
{
    public:
        /**
         * @brief Constructor, subscribe to LiDAR topic and open the CSV file.
         *
         * @param node Node handle
         * @param nh Private node handle
         */
        WriteCSV(ros::NodeHandle node, ros::NodeHandle nh)
        {
            lidar_sub = nh.subscribe("/hesai/pandar", 1000, &WriteCSV::callbackLidar, this);
            pathCSVFile = "timestamps.csv";
            CSVFile.open(pathCSVFile);
        }

        /**
         * @brief Destructor, close the CSV file.
         */
        ~WriteCSV()
        {
            CSVFile.close();
        }

        /**
         * @brief Callback on the LiDAR values to write timestamps values in a CSV file.
         *
         * @param lidar_msg PointCloud ROS message from the LiDAR.
         */
        void callbackLidar(const sensor_msgs::PointCloud2::ConstPtr& lidar_msg)
        {
            CSVFile << lidar_msg->header.seq;
            CSVFile << ",";
            CSVFile << lidar_msg->header.stamp.sec;
            CSVFile << ".";
            int temp = lidar_msg->header.stamp.nsec;
            while(temp < 100000000)
            {
                CSVFile << "0";
                temp = temp * 10;
            }
            CSVFile << lidar_msg->header.stamp.nsec;
            CSVFile << "\n";
            ROS_INFO("Exported");
        }

    private:
        ros::Subscriber lidar_sub;
        std::ofstream CSVFile;
        std::string pathCSVFile;
};

/**
 * @brief Simple node creation calling the writeCSV class.
 *
 * @param argc
 * @param argv
 * @return 0
 */
int main(int argc, char **argv)
{
    ros::init(argc, argv, "csv");
    ros::NodeHandle nh("~");
    ros::NodeHandle node;
    WriteCSV writeCSV(node, nh);

    ros::spin();
    return 0;
}
