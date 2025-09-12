import { createContext, useContext } from 'react'

export interface WorkspaceContextBridge {
  isWorkspaceOpened: boolean
  setIsWorkspaceOpened: (val: boolean) => void
}

export const WorkspaceContext = createContext<WorkspaceContextBridge | null>(null)

export function useWorkspaceContext() {
  const cur_context = useContext(WorkspaceContext)
  if (!cur_context) {
    throw new Error('🔑 Workspace status is visited outside the context, please fix this error...')
  }
  return cur_context
}
