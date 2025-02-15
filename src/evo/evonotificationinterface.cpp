// Copyright (c) 2014-2019 The Dash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "evo/evonotificationinterface.h"

#include "evo/deterministicmns.h"
#include "evo/mnauth.h"
#include "llmq/quorums.h"
#include "llmq/quorums_chainlocks.h"
#include "llmq/quorums_dkgsessionmgr.h"
#include "validation.h"

void EvoNotificationInterface::InitializeCurrentBlockTip()
{
    LOCK(cs_main);
    deterministicMNManager->SetTipIndex(chainActive.Tip());
}

void EvoNotificationInterface::AcceptedBlockHeader(const CBlockIndex* pindexNew)
{
    llmq::chainLocksHandler->AcceptedBlockHeader(pindexNew);
}

void EvoNotificationInterface::UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload)
{
    // background thread updates
    llmq::chainLocksHandler->UpdatedBlockTip(pindexNew, pindexFork);
    llmq::quorumDKGSessionManager->UpdatedBlockTip(pindexNew, fInitialDownload);
    llmq::quorumManager->UpdatedBlockTip(pindexNew, pindexFork, fInitialDownload);
}

void EvoNotificationInterface::NotifyMasternodeListChanged(bool undo, const CDeterministicMNList& oldMNList, const CDeterministicMNListDiff& diff)
{
    CMNAuth::NotifyMasternodeListChanged(undo, oldMNList, diff);
}
