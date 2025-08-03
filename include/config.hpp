#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <chrono>
#include <functional>
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

namespace loadtest {

// Forward declarations
class ClientOpts;

// Configuration structures
struct PodSpec {
    std::map<std::string, std::string> labels;
    std::map<std::string, std::string> annotations;
    std::string name;
    std::string namespace_;
    std::string serviceAccountName;
    std::string configMapName;
    std::string image;
    std::vector<std::string> controllerCommand;
    std::vector<std::string> producerCommand;
    std::vector<std::string> consumerCommand;
    std::map<std::string, std::map<std::string, std::string>> resources;
};

struct Metrics {
    std::string endpoint;
    std::string format; // json, csv, etc.
};

struct Controller {
    std::string recordDirectory;
    std::string logLevel;
};

struct AdminClient {
    std::string certificate;
    std::string privateKey;
    std::string authType; // basic, oauth, etc.
};

enum class ConsumerMode {
    FANOUT,
    SHARED,
    ROUND_ROBIN
};

struct Consumer {
    bool ignoreErrors;
    int pods;
    int consumersPerPod;
    ConsumerMode mode;
    std::string consumerGroupName;
    int32_t maxBatchSize;
    std::string endpoint;
    std::string protocol; // http, grpc, tcp, etc.
};

struct Endpoint {
    std::string name;
    std::string url;
    std::string method; // GET, POST, PUT, etc.
    std::map<std::string, std::string> headers;
    std::string body;
    int32_t timeout;
    int32_t retries;
};

struct Producer {
    Endpoint endpoint;
    bool useAsync;
    int32_t parallelism;
    int producersPerPod;
    uint64_t throughput;  // requests per second
    uint batchCount;
    uint64_t messageSize;
    uint64_t maxBytes;
    int maxBufferedRecords;
    int count;
    std::string compression;
    std::string contentType;
    std::chrono::milliseconds lingerMs;
    bool staticValue;
    std::string staticContent;
    std::string retryPolicy;
    std::vector<std::string> producerConfig;
};

struct Events {
    std::string topic;
    std::string broker;
    std::string format;
};

struct Logging {
    std::string level;
    std::string format; // json, text
    struct {
        std::string producer;
        std::string consumer;
    } components;
};

// Main configuration class
class Config {
public:
    Config();
    ~Config();

    // Load configuration from files
    bool loadFromFiles(const std::vector<std::string>& configFiles);
    
    // Load configuration from YAML string
    bool loadFromYaml(const std::string& yamlContent);
    
    // Get configuration values
    const std::vector<std::string>& getEndpoints() const { return endpoints_; }
    const std::string& getMode() const { return mode_; }
    const std::string& getAuthMode() const { return authMode_; }
    const std::string& getCertificate() const { return certificate_; }
    const std::string& getPrivateKey() const { return privateKey_; }
    const std::string& getCACert() const { return caCert_; }
    uint16_t getJobs() const { return jobs_; }
    std::chrono::seconds getLength() const { return length_; }
    
    const PodSpec& getPods() const { return pods_; }
    const Controller& getController() const { return controller_; }
    const AdminClient& getAdminClient() const { return adminClient_; }
    const Producer& getProducer() const { return producer_; }
    const Consumer& getConsumer() const { return consumer_; }
    const Metrics& getMetrics() const { return metrics_; }
    const Events& getEvents() const { return events_; }
    const Logging& getLogging() const { return logging_; }
    
    // Client options
    std::shared_ptr<ClientOpts> getClientOpts() const;
    
    // Validation
    bool validate() const;
    std::vector<std::string> getValidationErrors() const;

private:
    // Configuration data
    std::vector<std::string> endpoints_;
    std::string mode_;
    std::string authMode_;
    std::string certificate_;
    std::string privateKey_;
    std::string caCert_;
    uint16_t jobs_;
    std::chrono::seconds length_;
    
    PodSpec pods_;
    Controller controller_;
    AdminClient adminClient_;
    Producer producer_;
    Consumer consumer_;
    Metrics metrics_;
    Events events_;
    Logging logging_;
    
    // Internal state
    YAML::Node configNode_;
    std::vector<std::string> validationErrors_;
    std::shared_ptr<ClientOpts> clientOpts_;
    
    // Helper methods
    bool parseYamlNode(const YAML::Node& node);
    bool validateTLSFiles() const;
    void setDefaults();
};

// Utility functions
std::string consumerModeToString(ConsumerMode mode);
ConsumerMode stringToConsumerMode(const std::string& str);

} // namespace loadtest 