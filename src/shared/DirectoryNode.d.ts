export type DirectoryNode = {
  path: string
  display_name: string
  is_folder: boolean
  children?: DirectoryNode[]
}
