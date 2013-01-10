/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (c) 2012 The Linux Foundation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _COMMANDLISTENER_H__
#define _COMMANDLISTENER_H__

#include <pthread.h>
#include <sysutils/FrameworkListener.h>

#include "NetdCommand.h"
#include "TetherController.h"
#include "NatController.h"
#include "PppController.h"
#include "PanController.h"
#include "SoftapController.h"
#include "BandwidthController.h"
#include "IdletimerController.h"
#include "ResolverController.h"
#include "SecondaryTableController.h"
#include "RouteController.h"

class CommandListener : public FrameworkListener {
    static TetherController *sTetherCtrl;
    static NatController *sNatCtrl;
    static PppController *sPppCtrl;
    static PanController *sPanCtrl;
    static SoftapController *sSoftapCtrl;
    static BandwidthController *sBandwidthCtrl;
    static IdletimerController *sIdletimerCtrl;
    static ResolverController *sResolverCtrl;
    static SecondaryTableController *sSecondaryTableCtrl;
    static RouteController *sRouteCtrl;

public:
    CommandListener();
    virtual ~CommandListener() {}

private:

    static int writeFile(const char *path, const char *value, int size);

    static int readInterfaceCounters(const char *iface, unsigned long *rx, unsigned long *tx);

    class SoftapCmd : public NetdCommand {
    public:
        SoftapCmd();
        virtual ~SoftapCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class InterfaceCmd : public NetdCommand {
    public:
        InterfaceCmd();
        virtual ~InterfaceCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class IpFwdCmd : public NetdCommand {
    public:
        IpFwdCmd();
        virtual ~IpFwdCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class TetherCmd : public NetdCommand {
    public:
        TetherCmd();
        virtual ~TetherCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class V6RtrAdvCmd: public NetdCommand {
    public:
        V6RtrAdvCmd();
        virtual ~V6RtrAdvCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class NatCmd : public NetdCommand {
    public:
        NatCmd();
        virtual ~NatCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class ListTtysCmd : public NetdCommand {
    public:
        ListTtysCmd();
        virtual ~ListTtysCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class PppdCmd : public NetdCommand {
    public:
        PppdCmd();
        virtual ~PppdCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class PanCmd : public NetdCommand {
    public:
        PanCmd();
        virtual ~PanCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class BandwidthControlCmd : public NetdCommand {
    public:
        BandwidthControlCmd();
        virtual ~BandwidthControlCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    protected:
        void sendGenericOkFail(SocketClient *cli, int cond);
        void sendGenericOpFailed(SocketClient *cli, const char *errMsg);
        void sendGenericSyntaxError(SocketClient *cli, const char *usageMsg);
    };

    class IdletimerControlCmd : public NetdCommand {
    public:
        IdletimerControlCmd();
        virtual ~IdletimerControlCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class ResolverCmd : public NetdCommand {
    public:
        ResolverCmd();
        virtual ~ResolverCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class RouteCmd : public NetdCommand {
    public:
        RouteCmd();
        virtual ~RouteCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);
    };

    class RtSolCmd : public NetdCommand {
    public:
        RtSolCmd();
        virtual ~RtSolCmd() {}
        int runCommand(SocketClient *c, int argc, char ** argv);

    class GwWorkerThreadPool {
        private:
            pthread_mutex_t mRefMutex;
            int mRefCount;
        public:
            static const int MAX_V6_GATEWAY_WORKER_THREADS  = 5;
            GwWorkerThreadPool();
            virtual ~GwWorkerThreadPool();
            void incrementRefCount();
            void decrementRefCount();
            bool isPoolFull();
            int getRefCount();
            pthread_t mThreadPool[MAX_V6_GATEWAY_WORKER_THREADS];

    };

    class V6GatewayHandler {
        public:
            V6GatewayHandler(SocketClient *c, char *netIf);
            int getGateway(int rs_sock_fd, int ra_sock_fd, char * netIf,
                    char *gateway, unsigned int *lease);
            void start();
            static void *threadStart(void *pV6GatewayHandler);
            ~V6GatewayHandler();
        private:
            void run();
            int createRaSocket(char *netIf);
            int createRsSocket(char *netIf);
            int getProperty(const char * const propertyKey,
                                    const char * const defaultValue);
            SocketClient* mClient;
            char* mNetIf;
            int mCmdNum;
        };
    };

    static RtSolCmd::GwWorkerThreadPool *sGwThreadPool;
};

#endif
