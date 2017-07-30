; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_none.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_none(%struct.archive* %a) #0 !dbg !4 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !15, metadata !16), !dbg !17
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !18
  ret i32 0, !dbg !19
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_none(%struct.archive* %a) #0 !dbg !11 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !20, metadata !16), !dbg !21
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !22
  ret i32 0, !dbg !23
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!12, !13}
!llvm.ident = !{!14}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_none.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !11}
!4 = distinct !DISubprogram(name: "archive_write_set_compression_none", scope: !1, file: !1, line: 32, type: !5, isLocal: false, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 179, flags: DIFlagFwdDecl)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = distinct !DISubprogram(name: "archive_write_add_filter_none", scope: !1, file: !1, line: 39, type: !5, isLocal: false, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !{i32 2, !"Dwarf Version", i32 4}
!13 = !{i32 2, !"Debug Info Version", i32 3}
!14 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!15 = !DILocalVariable(name: "a", arg: 1, scope: !4, file: !1, line: 32, type: !8)
!16 = !DIExpression()
!17 = !DILocation(line: 32, column: 52, scope: !4)
!18 = !DILocation(line: 34, column: 8, scope: !4)
!19 = !DILocation(line: 35, column: 2, scope: !4)
!20 = !DILocalVariable(name: "a", arg: 1, scope: !11, file: !1, line: 39, type: !8)
!21 = !DILocation(line: 39, column: 47, scope: !11)
!22 = !DILocation(line: 41, column: 8, scope: !11)
!23 = !DILocation(line: 42, column: 2, scope: !11)
