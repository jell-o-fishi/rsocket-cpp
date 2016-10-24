// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include "src/ConnectionSetupPayload.h"
#include "src/RequestHandler.h"

namespace reactivesocket {

class NullSubscriber : public Subscriber<Payload> {
 public:
  // Subscriber methods
  void onSubscribe(std::shared_ptr<Subscription> subscription) override;
  void onNext(Payload element) override;
  void onComplete() override;
  void onError(folly::exception_wrapper ex) override;
};

class NullSubscription : public Subscription {
 public:
  // Subscription methods
  void request(size_t n) override;
  void cancel() override;
};

class NullRequestHandler : public RequestHandler {
 public:
  std::shared_ptr<Subscriber<Payload>> handleRequestChannel(
      Payload request,
      const std::shared_ptr<Subscriber<Payload>>& response) override;

  void handleRequestStream(Payload request, const std::shared_ptr<Subscriber<Payload>>& response)
      override;

  void handleRequestSubscription(Payload request, const std::shared_ptr<Subscriber<Payload>>& response)
      override;

  void handleRequestResponse(Payload request, const std::shared_ptr<Subscriber<Payload>>& response)
      override;

  void handleFireAndForgetRequest(Payload request) override;

  void handleMetadataPush(std::unique_ptr<folly::IOBuf> request) override;

  void handleSetupPayload(ConnectionSetupPayload request) override;
};

using DefaultRequestHandler = NullRequestHandler;
}
