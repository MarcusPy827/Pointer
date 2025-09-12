export type DirectoryExistResult = {
  result: boolean
  result_msg: string
}

export type WorkspaceInfoQueryPayload = {
  query_state: boolean
  err_msg: string
  err_code: number
  name: string
  owner_uid: string
  owner_name: string
  config_updated: number
  created_at: number
  version: number
  min_compatible_version: number
}
